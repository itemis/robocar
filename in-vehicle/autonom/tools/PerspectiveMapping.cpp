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

/**
 * cheese
 1065  cheese /dev/video1
 1066  cheese /dev/video0

	eog


 */
#include "UndistortViewer.h"
#include "JConfig.h"
#include "JsonHelper.h"
#include "../cv/CameraFactory.h"
#include "../cvpipe/CvPipeFactory.h"
#include "../display/DisplayFactory.h"


#include "spdlog/spdlog.h"

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#include "../cv/CVUtil.h"

#include <future>
#include <iostream>

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdio>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <algorithm>    // std::sort

#include "FunctionModeManager.h"
using namespace cv;
using namespace std;

JConfig jconfig;

FunctionModeManager functionModeManager;
bool yFunc(Point2f i, Point2f j) {
	return (i.y < j.y);
}
bool xFunc(Point2f i, Point2f j) {
	return (i.x < j.x);
}

std::string asyncLine() {
	string line;
	getline(cin, line);
	return line;
}

Mat findScaledHomography(vector<Point2f> &corners, vector<Point2f> &dst, double scalef) {
	 std::transform(corners.begin(), corners.end(), corners.begin(),
     			 [scalef](Point2f c) -> Point2f  { return Point2f(c.x *scalef, c.y * scalef );});
	for (auto v : corners) {
		cout << v << endl;
	}

	 std::transform(dst.begin(), dst.end(), dst.begin(),
	                  			 [scalef](Point2f c) -> Point2f  { return Point2f(c.x *scalef, c.y * scalef );});

	 auto homographyMat = findHomography(corners, dst);
	 cout << homographyMat << endl;

	 return homographyMat;

}


/*
 * Pictures must have a certain size. Started to work only with 640x480
 */
int main(int argc, char *argv[]) {

	jconfig.merge(argc, argv);

	AbstractCamera * camera = createCamera();
	CvPipe *pipe = createCvPipe();
	robocar::Display * display = new robocar::Display(nullptr);
	spdlog::set_level(spdlog::level::info);
	spdlog::info("Started");

	auto future = std::async(std::launch::async, asyncLine);
	
	// Size of chessboard, width and height
	auto config = jconfig.getIndirection("perspective-mapping");
	Size patternsize = json2Size(config["chessboard"]["size"]);
	// Size of a sequae
	double checker_length = config["chessboard"]["mm"].get<double>();
	double innerDistance = patternsize.height * checker_length;

	double scalef = 0.5;

	bool isInit = false;
int ypos=0;
int pixels_per_square =  0;
int xpos = 0;

	json jout;
	while (true) {
		cv::Mat img;
		//	std::cout << "\033[2J" << std:: endl;
		spdlog::debug("Capture");

		camera->captureVideo(img);
		spdlog::debug("Resize");
		img = pipe->resizeAndDistort(img);
		if(!isInit) {
			ypos = img.size().height-(img.size().height * 1 ) / 3 ;
			pixels_per_square = (img.size().height - ypos)/patternsize.height;
			xpos = img.size().width / 2 - (pixels_per_square * patternsize.width)/2;
			spdlog::info("Data {0} {1} {2}", xpos, ypos, pixels_per_square);
		}
		spdlog::debug("1");

		

		if (true
				|| future.wait_for(std::chrono::seconds(0))
						== std::future_status::ready) {
			vector<Point2f> corners; //this will be filled by the detected corners
			//auto line = future.get();
			//future = std::async(std::launch::async, asyncLine);
			//   Number of inner corners per a chessboard row and column ( patternSize = cvSize(points_per_row,points_per_colum) = cvSize(columns,rows) ).

			// Out patternis 6 wide and 8 long when put on the floor in lateral direction
			
			


			//cout << "Checking" << endl;
			bool patternfound = findChessboardCorners(img, patternsize, corners,
					CALIB_CB_ADAPTIVE_THRESH // + CALIB_CB_NORMALIZE_IMAGE
							//+ CALIB_CB_FAST_CHECK
);

			drawChessboardCorners( img, patternsize, Mat(corners), patternfound );
display->display(img);
			spdlog::debug("Done ");
			spdlog::debug(corners.size());
			if (patternfound) {
				std::sort(corners.begin(), corners.end(), yFunc);
if(true) {
				for (int i = 0; i < patternsize.height; i++) {
					std::sort(corners.begin() + (i * patternsize.width),
							corners.begin()

									+ (i * patternsize.width
											+ patternsize.width ), xFunc);
				}}

	vector<Point2f> dst;

				for (int y = 0; y < patternsize.height; y++)
					for (int x = 0; x < patternsize.width; x++) {
						Point2f p(xpos + x * pixels_per_square,
								ypos+ y * pixels_per_square);
						dst.push_back(p);
					}


				 auto homographyMat = findScaledHomography(corners, dst, scalef);


				Mat warpedImg ;

				cv::warpPerspective(img,warpedImg,homographyMat,img.size());
				display->display(warpedImg);

//				 FileStorage fs("warp.json", FileStorage::WRITE);
//				fs << "homography" << homographyMat;
//					fs.release();

				auto pixelSize = (dst.back().y-dst[0].y) / innerDistance;
				auto mmPerPixel = 1 / pixelSize;
				std::cout << "pix" << pixelSize << " " <<mmPerPixel << std::endl;
			}
		}
	}
}


UndistortViewer::UndistortViewer() {
	// TODO Auto-generated constructor stub

}

UndistortViewer::~UndistortViewer() {
	// TODO Auto-generated destructor stub
}

