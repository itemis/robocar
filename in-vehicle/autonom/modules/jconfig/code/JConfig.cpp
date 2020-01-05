/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG
 */

#include "JConfig.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <experimental/filesystem>

using nlohmann::json;
namespace fs = std::experimental::filesystem;
JConfig::JConfig()  {
	char * configfile = getenv("JCONFIG");
	if(configfile == nullptr)
		configfile = "config.json";
	auto in = std::ifstream(configfile);
	auto lj = new json;

	if(spdlog::get("jconfig"))
		logger = spdlog::get("jconfig");
	else
		logger = spdlog::stderr_color_mt("jconfig");

	j = json::parse(in);

	mergeAutomatic();
}

JConfig::~JConfig() {
	spdlog::drop("jconfig");
}

json JConfig::deref(std::string jpointer) {
	auto p = nlohmann::json_pointer<nlohmann::json>(jpointer);
	return j[p];
}

json JConfig::getIndirection(std::string origVaue) {
	auto ref = j[origVaue].get<std::string>();
	return deref(ref);

}

void JConfig::load(int argc, char *argv[]) {
	std::vector<std::string> arguments(argv + 1, argv + argc);
	if(arguments.size() > 0)
		load(arguments);
}

void JConfig::mergeFile(std::string fname) {
	auto in = std::ifstream(fname);
	auto j2 = json::parse(in);
	j.merge_patch(j2);
}
void JConfig::merge(int argc, char *argv[]) {
	std::vector<std::string> arguments(argv + 1, argv + argc);
	for(auto & arg :arguments) {
		logger->info("Checking to merge {0}", arg);
		if (arg.rfind("#", 0) == 0) {
			mergeFromString(arg.substr(1));
		} else {
			mergeFile(arg);
		}
	}

}

void JConfig::load(std::vector<std::string> filenames) {
	logger->debug("Reading "+filenames.at(0));
	auto in = std::ifstream(filenames.at(0));
	j = json::parse(in);

	for(int i=1; i<filenames.size();i++) {
		logger->debug("Reading "+filenames.at(i));
		in = std::ifstream(filenames.at(i));
		auto j2 = json::parse(in);
		j.merge_patch(j2);
	}

	if(j.find("json-include") != j.end()) {
		logger->debug("Reading Included files");
		for(int i = 0; i< j["json-include"].size();i++) {
			logger->debug("Reading "+j["json-include"][i].get<std::string>());
			in = std::ifstream(j["json-include"][i].get<std::string>());
			auto j2 = json::parse(in);
			j.merge_patch(j2);
		}
	}
}



void JConfig::mergeFromString(std::string text) {
	json j2;
	std::stringstream str;
	str << text;
	str >> j2;
	j.merge_patch(j2);

}

void JConfig::setFromString(std::string text) {
	std::stringstream str;
	str << text;
	str >> j;
}

void JConfig::mergeAutomatic() {
	char buf[256];
	if( 0== gethostname(buf,sizeof(buf)) ) {
		std::string fname(buf);
		fname.append(".json");
		logger->info("Checking for {0}", fname);
		if(fs::exists("helloworld.txt") ) {
			logger->info("Merging {0}", fname);
			mergeFile(fname);
		}
	}

}

