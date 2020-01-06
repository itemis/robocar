/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 2019 initial Contribution
 */

#include "UndistortViewer.h"
#include "JConfig.h"
#include "../cv/CameraFactory.h"
#include "../cvpipe/CvPipeFactory.h"
#include "../display/DisplayFactory.h"
#include "VirtualTrack.h"

#include "spdlog/spdlog.h"

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#include "../cv/CVUtil.h"
#include "GeoLocationFactory.h"
#include "FunctionModeManager.h"

#include <iostream>
#include <chrono>
JConfig jconfig;

FunctionModeManager functionModeManager;

#define PROF_S(NAME)  auto t_ ## NAME ## _s = std::chrono::high_resolution_clock::now();
#define PROF_E(NAME)  auto t_ ## NAME ## _e = std::chrono::high_resolution_clock::now();  double elapsed_ ## NAME = std::chrono::duration<double, std::milli>(t_ ## NAME ## _e - t_ ## NAME ## _s).count();

#define PROF_L(NAME, V) 	spdlog::debug("Elapsed " V " {0}", elapsed_ ## NAME);
int main(int argc, char *argv[]) {

	jconfig.merge(argc, argv);

	AbstractCamera *camera = createCamera();
	CvPipe *pipe = createCvPipe();
	robocar::Display *display = new robocar::Display(nullptr);
	spdlog::set_level(spdlog::level::debug);
	spdlog::info("Started");

	VirtualTrack track;

	int xpos = 750;

	AbstractGeolocation *geo = createGeolocation();

	auto homographyMat = getHomography(jconfig);
	std::cout << homographyMat << std::endl;

	auto birdview = jconfig.j["ar-viewer"]["birds-view"].get<bool>();
	spdlog::info("Showing birdview: {0}", birdview);
	double angle = 90.0;

	while (true) {

		auto t_start = std::chrono::high_resolution_clock::now();

		cv::Mat img;
		//	std::cout << "\033[2J" << std:: endl;
		spdlog::debug("Capture");

		PROF_S(CAPTURE)
		camera->captureVideo(img);
		if(img.empty())
			spdlog::critical("No image from camera");
		PROF_E(CAPTURE);
		PROF_L(CAPTURE, "Capture");
		spdlog::debug("Resize");
		img = pipe->resizeAndDistort(img);

		spdlog::info("1");
		double o;
		millimeter_t x, y;

		geo->getLocation(x, y, o);

		if (!geo->isPlausible(x, y)) {
			spdlog::debug("Implausible values from geolocation");
			continue;
		}
		track.virtualize(img, x, y, o);

//		angle +=10;
		if (angle >= 360)
			angle = 0;
		spdlog::debug("Display");
		display->display(img);

	}

}
UndistortViewer::UndistortViewer() {
	// TODO Auto-generated constructor stub

}

UndistortViewer::~UndistortViewer() {
	// TODO Auto-generated destructor stub
}

