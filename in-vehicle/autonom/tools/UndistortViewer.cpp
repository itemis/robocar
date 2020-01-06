/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 20.03.2019 initial Contribution
 */

#include "UndistortViewer.h"
#include "JConfig.h"
#include "../cv/CameraFactory.h"
#include "../cvpipe/CvPipeFactory.h"
#include "../display/DisplayFactory.h"

#include "spdlog/spdlog.h"
#include <iostream>

#include <opencv2/opencv.hpp>
#include "FunctionModeManager.h"
JConfig jconfig;

FunctionModeManager functionModeManager;
int main(int argc, char *argv[]) {

	std::vector<std::string> arguments(argv + 1, argv + argc);
	if(arguments.size() > 0)
		jconfig.load(arguments);

	AbstractCamera * camera=createCamera();
	CvPipe *pipe = createCvPipe();
	robocar::Display * display = new robocar::Display(nullptr);
	spdlog::set_level(spdlog::level::debug);
	spdlog::info("Started");
	//std::cout << pipe->homographyMat << std::endl;
	while(true) {
		cv::Mat img;
		spdlog::debug("Capture");

		camera->captureVideo(img);
		spdlog::debug("Resize");
		img = pipe->resizeAndDistort(img);
		cv::Mat x;
		
		img = pipe->warpPerspective(img);
		std::cout << img.size() << std::endl;
		//cv::warpPerspective(img,x,pipe->homographyMat,img.size());
		spdlog::debug("Display");
		display->display(x);
	}



}
UndistortViewer::UndistortViewer() {
	// TODO Auto-generated constructor stub

}

UndistortViewer::~UndistortViewer() {
	// TODO Auto-generated destructor stub
}

