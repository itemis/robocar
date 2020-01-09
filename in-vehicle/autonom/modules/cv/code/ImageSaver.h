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

#ifndef CV_IMAGESAVER_H_
#define CV_IMAGESAVER_H_


#include "AbstractImageSaver.h"
#include <fmt/format.h>

class ImageSaver : public AbstractImageSaver {
protected:
	const std::string p;
	const std::string f;
	std::string lp ;
	int count;
public:
	ImageSaver(std::string path, std::string filename);
	virtual ~ImageSaver();

	int save(cv::Mat im);
	int save(cv::Mat im, int arg1);
	int save(cv::Mat img,int arg1, std::chrono::system_clock::time_point& timestamp);
	std::string lastPath();
};

#endif /* CV_IMAGESAVER_H_ */
