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

#pragma once

#ifndef VIRTUALTRACK_H_
#define VIRTUALTRACK_H_

#include <opencv2/core/mat.hpp>
#include "GeoLocationFactory.h"

using namespace units::angle;

/**
 * Supports the augmented reality blending of a virtual track
 */
class VirtualTrack {

protected:

	// Provides the location
	AbstractGeolocation * geo;

	// Mat that is used to transform the top-down view of the
	// track segement to the perspective of the cam. Is camera
	// specific and is loaded from json configuration
	//
	cv::Mat homographyMat;

	// Initial offset on map
	cv::Point offset;

	// Information on of the map
	int width_in_mm;
	int pixelsize_mm;

	// Where on the map we consider the "north" to be
	degree_t virtual_north;

	bool visualize=false;
	int max_opaque = 128;

public:

	// Contains map data.
	cv::Mat texture;

	// Size of field ov fiew
	int fov = 0;

	VirtualTrack();
	virtual ~VirtualTrack();

	// Returns full field of view at position. This is all area that could
	// be seen, no matter of the orientation. Note that we optimize and return
	// rectangles, not circles.

	cv::Mat fullFieldOfView(int x, int y);

	// Rotate the matrix so that the track image is aligned so that the it looks like
	// we face the image north
	//
	cv::Mat rotate(cv::Mat& m, double orientation);
	cv::Mat visibleArea(cv::Mat& m);

	// Maps the size of the top down view of the visible part of the track
	// to the size of the top down view of the camera so that the track location
	// is correct
	cv::Mat mapFovToTopDown(cv::Mat& fov,cv::Mat &ref, int ref_pixsize_inmm);

	// Blend two images based on the alpha channel on the 2nd image.
	void blend(cv::Mat& dst, cv::Mat aImage, int xPos, int yPos);

	/**
	 * Virtualize the track:
	 *
	 * img: Camera Image
	 * xPos, yPos and orientation: position of the car
	 *
	 * Blends the track at the given position into img.
	 */
	void virtualize(cv::Mat& img, millimeter_t xPos, millimeter_t  yPos,
			double orientation);

	degree_t adjustAngle(degree_t val) ;
	degree_t adjustAngle(double val) ;
};

#endif /* VIRTUALTRACK_H_ */
