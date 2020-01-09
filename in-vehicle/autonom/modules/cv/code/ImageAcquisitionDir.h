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


#ifndef CV_IMAGEACQUISITIONDIR_H_
#define CV_IMAGEACQUISITIONDIR_H_

#include "AbstractCamera.h"
#include <experimental/filesystem>
class ImageAcquisitionDir: public AbstractCamera {
private:
	std::experimental::filesystem::directory_iterator iterator;
public:
	ImageAcquisitionDir(const char * dirname);
	virtual ~ImageAcquisitionDir();

	virtual int initVideo() ;						//Initializes VideoCapture Object (opens camera modul via 4l2 camera driver)
	virtual int closeVideo() ;
	virtual int captureVideo(cv::Mat &dest) ;

};

#endif /* CV_IMAGEACQUISITIONDIR_H_ */
