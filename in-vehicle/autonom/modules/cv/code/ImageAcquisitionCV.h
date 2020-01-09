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


#ifndef CV_IMAGEACQUISITIONCV_H_
#define CV_IMAGEACQUISITIONCV_H_

#include "AbstractCamera.h"


#include <opencv2/videoio.hpp>



class ImageAcquisitionCV : public AbstractCamera {
	cv::VideoCapture cap;
public:
	ImageAcquisitionCV();
	ImageAcquisitionCV(int w, int h);
	ImageAcquisitionCV(const char * filename);
	virtual ~ImageAcquisitionCV();

	int initVideo();						//Initializes VideoCapture Object (opens camera modul via 4l2 camera driver)
	int closeVideo();
	int captureVideo(cv::Mat &dest);

};

#endif /* CV_IMAGEACQUISITIONCV_H_ */
