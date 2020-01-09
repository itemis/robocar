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
#include <experimental/filesystem>
class ImageAcquisitionFile: public AbstractCamera {
private:
	cv::Mat img;
public:
	ImageAcquisitionFile(std::string filename);
	virtual ~ImageAcquisitionFile();

	virtual int initVideo() ;						//Initializes VideoCapture Object (opens camera modul via 4l2 camera driver)
	virtual int closeVideo() ;
	virtual int captureVideo(cv::Mat &dest) ;

};


