/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 2019
 */



#include "JConfig.h"
#include "CameraFactory.h"


#include <chrono>

#include "spdlog/spdlog.h"
#include <fmt/format.h>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>



#include <iostream>
#include <string>

#define PROF_S(NAME)  auto t_ ## NAME ## _s = std::chrono::high_resolution_clock::now();
#define PROF_E(NAME)  auto t_ ## NAME ## _e = std::chrono::high_resolution_clock::now();  double elapsed_ ## NAME = std::chrono::duration<double, std::milli>(t_ ## NAME ## _e - t_ ## NAME ## _s).count();

#define PROF_L(NAME, V) 	spdlog::debug("Elapsed " V " {0}", elapsed_ ## NAME);

JConfig jconfig;

using namespace std::chrono;

int main(int argc, char *argv[]) {
	spdlog::info("Started camera delay. Make point your camera at the screen with these informations");
	jconfig.merge(argc,argv);

	AbstractCamera * camera=createCamera();

	spdlog::set_level(spdlog::level::debug);

	int counter = 0;

	while(true) {
		milliseconds ms = duration_cast< milliseconds >(
		    system_clock::now().time_since_epoch()
		);

		std::stringstream ss;
		ss << ms.count();

		std::cout << ss.str() << std::endl;

		cv::Mat capturedImage;
		PROF_S(CAPTURE)
		camera->captureVideo(capturedImage);
		std::cout << capturedImage.size().width << std::endl;
		PROF_E(CAPTURE)
		PROF_L(CAPTURE, "capture")

		std::string outfn = fmt::format("cap{0}_{1}.jpeg", ss.str(), counter);
		cv::imwrite(outfn,capturedImage);

		counter ++;
	}
}
