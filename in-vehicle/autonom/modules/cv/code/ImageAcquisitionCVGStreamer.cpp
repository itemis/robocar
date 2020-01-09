/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 25.02.2019 initial Contribution
 */


#include "ImageAcquisitionCVGStreamer.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <iostream>

#include <fmt/format.h>
#include <spdlog/spdlog.h>
using namespace std;
using namespace cv;


using namespace fmt;

std::string format_stream(std::string str, int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
	 return fmt::format(str,
			   "capture_width"_a = capture_width,
			   "capture_height"_a = capture_height,
			   "display_width"_a = display_width,
			   "display_height"_a = display_height,
			   "framerate"_a = framerate,
			   "flip_method"_a = flip_method);
}

std::string gstreamer_pipeline (std::string str, int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {

	auto formatted = fmt::format(str,
		   "capture_width"_a = capture_width,
		   "capture_height"_a = capture_height,
		   "display_width"_a = display_width,
		   "display_height"_a = display_height,
		   "framerate"_a = framerate,
		   "flip_method"_a = flip_method);


	spdlog::info( "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink");

	spdlog::info("Gstreamer: {}", formatted);
    return str;
}

ImageAcquisitionCVGStreamer::ImageAcquisitionCVGStreamer(std::string str) : cap(cv::VideoCapture(  gstreamer_pipeline(str, 1280,
		720,
		1280,
		720,
		30,
	2),CAP_GSTREAMER)) {
	// TODO Auto-generated constructor stub

}

ImageAcquisitionCVGStreamer::ImageAcquisitionCVGStreamer() : cap(cv::VideoCapture(  gstreamer_pipeline("", 1280,
		720,
		1280,
		720,
		30,
	2),CAP_GSTREAMER)) {
	// TODO Auto-generated constructor stub

}

ImageAcquisitionCVGStreamer::ImageAcquisitionCVGStreamer(const char * filename) : cap(cv::VideoCapture(filename)) {
	// TODO Auto-generated constructor stub

}

ImageAcquisitionCVGStreamer::~ImageAcquisitionCVGStreamer() {
	// TODO Auto-generated destructor stub
}

int ImageAcquisitionCVGStreamer::initVideo() {
	if(!cap.isOpened())
	{
		cout << "Could not open the cam module" << endl;
		return 0;
	}
//	cap.set(CAP_PROP_FPS, 60);							// used to set the fps rate of the camera module
	return 1;

}

int ImageAcquisitionCVGStreamer::captureVideo(cv::Mat& dest) {
//	cout << "Get Frame" << endl;
	cap  >> dest;
	return 0;
}

int ImageAcquisitionCVGStreamer::closeVideo() {

	if(cap.isOpened())
	{
		cap.release();
		return 1;
	}
	else
	{
		cout << "Could not close cam the cam module\n" << endl;
		return 0;
	}
	return 0;
}
