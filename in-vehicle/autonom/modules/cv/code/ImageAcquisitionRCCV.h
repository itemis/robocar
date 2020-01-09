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


#ifndef IMAGEACQUISTIONRCCV_H_
#define IMAGEACQUISTIONRCCV_H_


#include "AbstractCamera.h"


class ImageAcquisitionRCCV : public AbstractCamera {
private:
	void * camera = nullptr;
public:
	ImageAcquisitionRCCV();
	virtual ~ImageAcquisitionRCCV();

	int initVideo();						//Initializes VideoCapture Object (opens camera modul via 4l2 camera driver)
	int closeVideo();
	int captureVideo(cv::Mat &dest);

};

#endif /* IMAGEACQUISTIONRCCV_H_ */
