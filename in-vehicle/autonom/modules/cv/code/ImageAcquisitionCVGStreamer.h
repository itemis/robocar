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


#pragma once

#include "AbstractCamera.h"



#include <opencv2/videoio.hpp>

std::string format_stream(std::string str, int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) ;


class ImageAcquisitionCVGStreamer : public AbstractCamera {
	cv::VideoCapture cap;
public:
	ImageAcquisitionCVGStreamer();
	ImageAcquisitionCVGStreamer(std::string);
	ImageAcquisitionCVGStreamer(const char * filename);
	virtual ~ImageAcquisitionCVGStreamer();

	int initVideo();						//Initializes VideoCapture Object (opens camera modul via 4l2 camera driver)
	int closeVideo();
	int captureVideo(cv::Mat &dest);

};


