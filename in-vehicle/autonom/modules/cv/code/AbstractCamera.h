/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 26.02.2019 initial Contribution
 */
#ifndef CV_ABSTRACTCAMERA_H_
#define CV_ABSTRACTCAMERA_H_

#include <opencv2/core/mat.hpp>


class AbstractCamera {
public:
	AbstractCamera();
	virtual ~AbstractCamera();

	virtual int initVideo() = 0;						//Initializes VideoCapture Object (opens camera modul via 4l2 camera driver)
	virtual int closeVideo() = 0;
	virtual int captureVideo(cv::Mat &dest) = 0;
};

#endif /* CV_ABSTRACTCAMERA_H_ */
