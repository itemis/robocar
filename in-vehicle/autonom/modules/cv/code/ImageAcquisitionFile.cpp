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


#include "ImageAcquisitionFile.h"

#include <string>
#include <iostream>
#include <experimental/filesystem>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

namespace fs = std::experimental::filesystem;


ImageAcquisitionFile::ImageAcquisitionFile(std::string filename)  {

	std::cout << "file image reader " << std::endl;
	img = cv::imread(filename);

}

ImageAcquisitionFile::~ImageAcquisitionFile() {
	// TODO Auto-generated destructor stub
}

int ImageAcquisitionFile::initVideo() {return 0;}						//Initializes VideoCapture Object (opens camera modul via 4l2 camera driver)
int ImageAcquisitionFile::closeVideo() {return 0;}
int ImageAcquisitionFile::captureVideo(cv::Mat &dest) {

	img.copyTo(dest);
	return 0;
}
