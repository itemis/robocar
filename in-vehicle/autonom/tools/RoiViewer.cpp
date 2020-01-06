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
#include <signal.h>
#include <opencv2/highgui/highgui.hpp>
#include "FunctionModeManager.h"
JConfig jconfig;


FunctionModeManager functionModeManager;

cv::Mat capture, distort, roi, grid;

bool flag = true;
void ctrlc_handler(int s ) {
	flag= false;
}


int main(int argc, char *argv[]) {

	   struct sigaction sigIntHandler;

	   sigIntHandler.sa_handler = ctrlc_handler;
	   sigemptyset(&sigIntHandler.sa_mask);
	   sigIntHandler.sa_flags = 0;



	std::vector<std::string> arguments(argv + 1, argv + argc);
	if(arguments.size() > 0)
		jconfig.load(arguments);

	AbstractCamera * camera=createCamera();
	CvPipe *pipe = createCvPipe();
	robocar::Display * display = new robocar::Display(nullptr);
	spdlog::set_level(spdlog::level::debug);
	spdlog::info("Started");


    sigaction(SIGINT, &sigIntHandler, nullptr);
	while(flag) {

		spdlog::debug("Capture");

		camera->captureVideo(capture);
		spdlog::debug("Resize");
		distort = pipe->resizeAndDistort(capture);
		roi = pipe->roi(distort);
		roi.copyTo(grid);
			pipe->drawGrid(grid);
		spdlog::debug("Display");
		display->display(grid);

	}

	cv::imwrite("roi.jpeg",capture);
	cv::imwrite("roi_distort.jpeg",distort);
	cv::imwrite("roi_roi.jpeg",roi);
	cv::imwrite("roi_grid.jpeg", grid);



}
UndistortViewer::UndistortViewer() {
	// TODO Auto-generated constructor stub

}

UndistortViewer::~UndistortViewer() {
	// TODO Auto-generated destructor stub
}

