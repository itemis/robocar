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


#include <ctime>
#include <iostream>
#include <raspicam/raspicam_cv.h>
#include "ImageAcquisitionRCCV.h"

using namespace std;




ImageAcquisitionRCCV::ImageAcquisitionRCCV()  {
	camera = new raspicam::RaspiCam_Cv();
}

ImageAcquisitionRCCV::~ImageAcquisitionRCCV() {


}

int ImageAcquisitionRCCV::initVideo() {
	raspicam::RaspiCam_Cv * cam = (raspicam::RaspiCam_Cv *) camera;

	//set camera params
		cam->set( cv::CAP_PROP_FORMAT, CV_8UC1 );
		//Open camera
		cout<<"Opening Camera..."<<endl;
		if (!cam->open()) {cerr<<"Error opening the camera"<<endl;return -1;}
}

int ImageAcquisitionRCCV::captureVideo(cv::Mat& dest) {
	raspicam::RaspiCam_Cv * cam = (raspicam::RaspiCam_Cv *) camera;

	cam->grab();
	cam->retrieve ( dest);

	return 0;


}

int ImageAcquisitionRCCV::closeVideo() {
	raspicam::RaspiCam_Cv * cam = (raspicam::RaspiCam_Cv *) camera;
	cam->release();
}
