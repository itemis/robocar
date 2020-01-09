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


#include "ImageAcquisitionCV.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
using namespace std;
using namespace cv;
ImageAcquisitionCV::ImageAcquisitionCV() : cap(cv::VideoCapture(0)) {
	// TODO Auto-generated constructor stub

}

ImageAcquisitionCV::ImageAcquisitionCV(int w, int h) : cap(cv::VideoCapture(0, CAP_V4L2)) {
	spdlog::info("Setting caps");
	 cap.set(CAP_PROP_FRAME_WIDTH, w);
	 cap.set(CAP_PROP_FRAME_HEIGHT, h);
	 spdlog::info("Setting caps done");
}


ImageAcquisitionCV::ImageAcquisitionCV(const char * filename) : cap(cv::VideoCapture(filename)) {
	// TODO Auto-generated constructor stub

}

ImageAcquisitionCV::~ImageAcquisitionCV() {
	// TODO Auto-generated destructor stub
}

int ImageAcquisitionCV::initVideo() {
	if(!cap.isOpened())
	{
		cout << "Could not open the cam module" << endl;
		return 0;
	}
	cap.set(CAP_PROP_FPS, 60);							// used to set the fps rate of the camera module
	return 1;

}

int ImageAcquisitionCV::captureVideo(cv::Mat& dest) {
//	cout << "Get Frame" << endl;
	cap  >> dest;
}

int ImageAcquisitionCV::closeVideo() {

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
