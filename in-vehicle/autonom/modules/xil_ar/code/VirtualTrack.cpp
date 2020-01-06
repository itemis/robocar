/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 2019 initial Contribution
 */

#include "VirtualTrack.h"

#include "JConfig.h"
#include "JsonHelper.h"
#include "../cv/CVUtil.h"

#include <iostream>
#include <string>
#include <algorithm>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

//#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

#include <units.h>
#include <cmath>

using namespace units::literals;
using namespace units::length;
using namespace units;

extern JConfig jconfig;
using namespace cv;

VirtualTrack::VirtualTrack() {

	auto j = jconfig.getIndirection("virtual-track");
	// Read the texture of the track, incl. alpha channel
	// IMREAD_UNCHANGED keeps alpha
	//
	cv::Mat dummy = cv::imread(j["texture"].get<std::string>(),
			cv::IMREAD_UNCHANGED);

	// Read the size of our field of view
	fov = j["fov"].get<int>();

	// An offset for measured coordinates and real coordinates. That allows us
	// to easily position the car without tweaking map or location
	//
	offset = json2Point(j["center-offset"]);
	virtual_north = make_unit<degree_t>(j["virtual-north"].get<double>());

	visualize = j.value("visualize", false);
	spdlog::info("Visualization of virtual track pipeline {0}", visualize);

	max_opaque = j["max-opaque"].get<int>();

	// This is the size of the track that we expect. This might not be the size of
	// the image in pixels, so we rescale so that 1px = 1cm
	//
	auto width_in_cm = j["width-in-cm"].get<int>();
	width_in_mm = width_in_cm * 10;
	// Scale to the size of the track that we expect
	//
	if (dummy.empty()) {
		spdlog::error("Texture Map is empty");
	}
	cv::resize(dummy, dummy,
			cv::Size(width_in_cm, (width_in_cm * dummy.rows) / dummy.cols));

	pixelsize_mm = width_in_mm / dummy.size().width;

	// We add a border of the size of the field of view that we expect to be avoid wrap around of the camera
	// at the borders

	copyMakeBorder(dummy, texture, fov, fov, fov, fov, cv::BORDER_CONSTANT,
			cv::Scalar(0, 0, 0, 0));
//	std::cout << texture.size << std::endl;

	geo = createGeolocation();

	homographyMat = getHomography(jconfig).inv();
	spdlog::trace("Loaded Homography");
//	std::cout << homographyMat << std::endl;
}

VirtualTrack::~VirtualTrack() {
	// TODO Auto-generated destructor stub
}

// Get a rectangle with the full field of view (ie fov in all directions)
// Note that return value is a part of the original matrix and
// should not be modified.
//
cv::Mat VirtualTrack::fullFieldOfView(int x, int y) {
	cv::Mat r;

	// Make sure that height and with are uneven numbers, so that
	// we have a "real" center pixel
	//
	// fov is factored out, original expressions are offset.x  + x +fov - fov
	//
	cv::Rect crop(offset.x + x, offset.y + y, 2 * fov + 1, 2 * fov + 1);
	r = cv::Mat(texture, crop);
	return r;

}

//
//  Rotation angle in degrees. Positive values mean counter-clockwise rotation (the coordinate origin is assumed to be the top-left corner).
//
// Since the visibleArea is taken from the upper have, we should not have a rotation when looking north in terms of
// the map (not real north)
// 

cv::Mat VirtualTrack::rotate(cv::Mat &m, double orientation) {
	Mat result;
	auto M = getRotationMatrix2D(Point(m.cols / 2, m.rows / 2), orientation,
			1.0);
	warpAffine(m, result, M, Size(m.cols, m.rows));
	return result;
}

// What we see in front is now the upper fov reows ov the image.
//
cv::Mat VirtualTrack::visibleArea(cv::Mat &m) {
	cv::Rect crop(0, 0, 2 * fov + 1, fov + 1);
	return cv::Mat(m, crop);
}

degree_t VirtualTrack::adjustAngle(degree_t val) {
	return virtual_north - val;
}

degree_t VirtualTrack::adjustAngle(double val) {
	return adjustAngle(make_unit<degree_t>(val));
}

void VirtualTrack::blend(Mat &dst, Mat aImage, int xPos, int yPos) {

	// Get Max opaqueness

	Mat track = aImage;

	if (dst.rows - track.rows != 0 || dst.cols - track.cols != 0) {
//		copyMakeBorder(texture_fac, texture_fac, dst.rows - texture_fac.rows, 0,
//				dst.cols - texture_fac.cols, 0, cv::BORDER_CONSTANT, cv::Scalar(0));
		copyMakeBorder(track, track, dst.rows - track.rows, 0,
				dst.cols - track.cols, 0, cv::BORDER_CONSTANT,
				cv::Scalar(0, 0, 0, 0));
	}

	cv::parallel_for_(cv::Range(0, dst.rows),
			[&](const Range &range) -> void {
				for (int r = range.start; r < range.end; r++) {
					cv::Vec3b *pixel = dst.ptr<cv::Vec3b>(r);
					cv::Vec4b *track_pixel = track.ptr<cv::Vec4b>(r);

					for (int c = 0; c < dst.cols; c++) {

						if (track_pixel[c][3] > 0) {
							auto fac = std::min(track_pixel[c][3],
									(unsigned char) max_opaque); // Opaqueness and inverse opaqueness at given point
							auto inv_fac = 255 - fac;

							for (int channel = 0; channel < 3; channel++) {
								int sc_d = ((int) pixel[c][channel] * inv_fac)
										/ 255;
								int sc_t = ((int) track_pixel[c][channel] * fac)
										/ 255;
								pixel[c][channel] = sc_d + sc_t;
								//	pixel[c][channel] = track_pixel[c][channel];
							}
						}
					}
				}
			});

//	std::cout << dst.size << std::endl;

//    aImage.copyTo(dst.rowRange(yPos, yPos + aImage.rows).colRange(xPos, xPos + aImage.cols), alpha);
}

/**
 * Overlays camImage with a virtual view of the track.
 * camImage is being overwritten with the track overlaid.
 */
void VirtualTrack::virtualize(Mat &img, millimeter_t xPos, millimeter_t yPos,
		double orientation) {
	double o;

	bool birdview = false;

	// Get the location from the location service
	centimeter_t xc = xPos, yc = yPos;

	// Geth the track as it is visible with the fov limit in
	// all directions
	auto fov = fullFieldOfView(xc.value(), yc.value());

	degree_t realRot = adjustAngle(o);
	auto rot = rotate(fov, realRot.value());

	auto vis = visibleArea(rot);

	cv::Mat topDown = mapFovToTopDown(vis, img, 6);

	cv::Mat warpedImg;

	cv::warpPerspective(topDown, warpedImg, homographyMat, img.size()); // cv::INTER_LINEAR | cv::WARP_INVERSE_MAP);

	blend(img, warpedImg, 0, 0);

	if (visualize) {
		cv::imshow("rot-fov", rot);
		cv::waitKey(1);

		cv::imshow("vis-fov", vis);
		cv::waitKey(1);

		cv::imshow("vis-fov-topdown", topDown);
		cv::waitKey(1);

		cv::imshow("warp-fov", warpedImg);
		cv::waitKey(1);

		cv::imshow("blended", img);
		cv::waitKey(1);
	}

}

Mat VirtualTrack::mapFovToTopDown(cv::Mat &fov, cv::Mat &ref,
		int ref_pixsize_inmm) {
	Mat result, result2;
	std::cout << "mapTopDown " << pixelsize_mm << " " << ref_pixsize_inmm
			<< std::endl;
	if (pixelsize_mm != ref_pixsize_inmm) {
		double scaleFac = (double) pixelsize_mm / ref_pixsize_inmm;

		resize(fov, result,
				Size(fov.size().width * scaleFac,
						fov.size().height * scaleFac));
	}

	auto h = (result.size().width - ref.size().width) / 2;
	cv::Rect myROI(h, (result.size().height - ref.size().height),
			ref.size().width, ref.size().height);

	result2 = result(myROI);
	return result2;

}

