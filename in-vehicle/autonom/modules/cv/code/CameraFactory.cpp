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



#include "AbstractCamera.h"
#include "ImageAcquisitionCV.h"
#include "ImageAcquisitionCVGStreamer.h"
#if HAS_RASPICAM_CV
#include "ImageAcquisitionRCCV.h"
#endif
#include "ImageAcquisitionDir.h"
#include "ImageAcquisitionFile.h"

#include "JConfig.h"

#include <iostream>
#include <string>
#include <algorithm>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "V4L2.h"
#include "JsonHelper.h"


extern JConfig jconfig;

/**
 * Make the camera configuration visible externaly, so that others can find it (e.g. the cv pipe)
 *
 */




json findCameraConfig() {
	auto static logger = spdlog::stderr_color_mt("findCameraConfig");

	auto allCams = allCameraNames() ;
	std::string cam = "";
	std::cout << logger << std::endl;
	if(! (jconfig.j)["camera"].empty()) {
		logger->info( "Configured camera: {}",(jconfig.j)["camera"].get<std::string>() );
				cam = (jconfig.j)["camera"].get<std::string>();
	} else {
		for(auto &element : (jconfig.j)["cameras-auto-detect"].items() ) {
			if (std::find(allCams.begin(), allCams.end(), element.key()) != allCams.end()) {
				logger->info( "Auto config camera: {}",element.key() );
				cam = element.value();
			}
		}
	}
	/**
	 * If we didn't find a camera automatically, we try to use the one in the "camera" field.
	 */
	logger->info("Camera config {0}:", cam);
	if(cam.length() == 0) {
		logger->error("No Camera found");
		return nullptr;
	}
	auto c_config = jconfig.deref(cam);
	return c_config;
}

AbstractCamera * createCamera() {

	auto static logger = spdlog::stderr_color_mt("createCamera");
	logger -> info("createCamera");
	/**
	 * We first try to identify system cameras and then try to find the first
	 * entry in the json that actually corresponds to a camera.
	 */
	auto c_config = findCameraConfig();
	std::cout << c_config << std::endl;



	for(auto & element : c_config.items()) {
		std::cout << element << std::endl;
	}
	if(c_config["type"].get<std::string>().compare("video")==0) {
		auto filename = c_config["file"].get<std::string>();
		logger->info( "File based {}",filename.c_str() );
		return new ImageAcquisitionCV(filename.c_str());
	}
	if(c_config["type"].get<std::string>().compare("raspi")==0) {
		std::cout << "Raspi based camera "  << std::endl;
#if HAS_RASPICAM_CV
		return new ImageAcquisitionRCCV();
#else
		return nullptr;
#endif

	}
	if(c_config["type"].get<std::string>().compare("directory")==0) {
		auto filename = c_config["path"].get<std::string>();
		return new ImageAcquisitionDir(filename.c_str());
	}

	if(c_config["type"].get<std::string>().compare("file")==0) {
		auto filename = c_config["path"].get<std::string>();
		return new ImageAcquisitionFile(filename.c_str());
	}


	if(c_config["type"].get<std::string>().compare("gstreamer")==0) {
			return new ImageAcquisitionCVGStreamer(c_config["config"].get<std::string>());
	}
	logger->info("Fallback default OpenCV camera" );

	if(c_config.contains("resolution")) {

		auto size = json2Size(c_config["resolution"]);
		logger->info("with size" );
		auto x =  new ImageAcquisitionCV(size.width, size.height);
		logger->info("created" );
		return x;
	}
	else {
		logger->info("default params" );
		return new ImageAcquisitionCV();
	}
}

