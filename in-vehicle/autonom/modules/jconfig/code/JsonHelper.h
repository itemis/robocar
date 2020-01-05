/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 26.02.2019 initial Contribution
 */

#pragma once
#ifndef TESTS_JSONHELPER_H_
#define TESTS_JSONHELPER_H_

#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>

#include "nlohmann/json.hpp"
//#include "3rdparty/lohmann/include/nlohmann/json.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using nlohmann::json;

class JsonHelper {
public:
	JsonHelper();
	virtual ~JsonHelper();
};

inline cv::Size json2Size(json j) {
//	std::cout << "Size :" << j <<std::endl;
	cv::Size x(j[0].get<int>(),j[1].get<int>());
	return x;

}

inline cv::Rect json2Rect(json j) {
//	std::cout << "Size :" << j <<std::endl;
	cv::Rect x(j[0].get<int>(),j[1].get<int>(),j[2].get<int>(),j[3].get<int>());
	return x;

}

inline cv::Point json2Point(json j) {
	cv::Point x(j[0].get<int>(),j[1].get<int>());
	return x;
}

inline std::vector<double> json2Vec(json j) {
	std::vector<double> result;
	for(int i = 0 ; i < j.size(); i ++ )
		result.push_back(j[i].get<double>());
	return result;

}

inline cv::Mat json2Matrix( json j) {

		auto size = json2Size(j["size"]);
		cv::Mat mat(size, CV_64F);


	int i = 0;
	for(int y = 0; y < mat.size().height;y++) {
		for(int x = 0; x < mat.size().width;x++) {
			mat.at<double>(y,x) = (j["data"][x+y*mat.size().width]).get<double>();
		}
	}
	return mat;
}


inline spdlog::level::level_enum json2loglevel(json j) {
	std::string v = j.get<std::string>();

	return spdlog::level::from_str(v);
}

inline std::shared_ptr<spdlog::logger> json2logger(json j, const std::string& logger_name) {

	auto console = spdlog::get(logger_name);
	if(console)
		return console;

	console = spdlog::stderr_color_mt(logger_name);
	if(j.find("logger") != j.end() && j["logger"].find(logger_name) != j["logger"].end() && j["logger"][logger_name].find("level") != j["logger"][logger_name].end()  )
		console->set_level(json2loglevel(j["logger"][logger_name]["level"]));

	return console;
}


inline cv::Mat matrixFromJson(cv::Mat& m , json array) {
	int i = 0;
	for(int y = 0; y < m.size().height;y++) {
		for(int x = 0; x < m.size().width;x++) {
			m.at<double>(y,x) = array[i].get<double>();
			i++;
		}
	}
	return m;
}

#endif /* TESTS_JSONHELPER_H_ */
