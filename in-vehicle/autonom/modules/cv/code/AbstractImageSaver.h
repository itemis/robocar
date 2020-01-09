/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 27.12.2019 Created
 */

#ifndef CV_ABSTRACTIMAGESAVER_H_
#define CV_ABSTRACTIMAGESAVER_H_

#include <opencv2/core/mat.hpp>
#include <chrono>
class AbstractImageSaver {

public:
	AbstractImageSaver();
	virtual ~AbstractImageSaver();

	virtual int save(cv::Mat img) = 0;
	virtual int save(cv::Mat img,int arg1) = 0;
	virtual int save(cv::Mat img,int arg1, std::chrono::system_clock::time_point& timestamp) = 0;
	virtual std::string lastPath() = 0;

};

#endif /* CV_ABSTRACTIMAGESAVER_H_ */
