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

#include "ImageAcquisitionDir.h"

#include <string>
#include <iostream>
#include <experimental/filesystem>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

namespace fs = std::experimental::filesystem;


ImageAcquisitionDir::ImageAcquisitionDir(const char * dirname) :iterator(fs::directory_iterator(dirname)) {

	std::cout << "directory image reader " << std::endl;
}

ImageAcquisitionDir::~ImageAcquisitionDir() {
	// TODO Auto-generated destructor stub
}

int ImageAcquisitionDir::initVideo() {return 0;}						//Initializes VideoCapture Object (opens camera modul via 4l2 camera driver)
int ImageAcquisitionDir::closeVideo() {return 0;}
int ImageAcquisitionDir::captureVideo(cv::Mat &dest) {

	try {
		auto path = (*iterator).path();
		std::cout << "Reading file " << path << std::endl;
		dest = cv::imread((*iterator).path());
		iterator++;

		return 0;
	}
	catch(std::experimental::filesystem::v1::__cxx11::filesystem_error e) {

		return -1;
	}
}
