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

#include "ImageSaver.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <fmt/format.h>

using namespace fmt;

std::string serializeTimePoint( const std::chrono::system_clock::time_point& time, const std::string& format)
{
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    std::tm tm = *std::gmtime(&tt); //GMT (UTC)
    //std::tm tm = *std::localtime(&tt); //Locale time-zone, usually UTC by default.
    std::stringstream ss;
    ss << std::put_time( &tm, format.c_str() );
    return ss.str();
}




ImageSaver::ImageSaver(const std::string path, const std::string filename) : p(path), f(filename),count(0) {
	// TODO Auto-generated constructor stub

}

ImageSaver::~ImageSaver() {
	// TODO Auto-generated destructor stub
}
//, const Args& ... args
int ImageSaver::save(cv::Mat img) {
	auto filename = fmt::format(f, count++);
	auto fullpath = fmt::format("{0}/{1}", p, filename);
	lp = fullpath;

	return cv::imwrite(fullpath, img );


}

int ImageSaver::save(cv::Mat img, int arg1) {
	auto filename = fmt::format(f, count++,arg1);
	auto fullpath = fmt::format("{0}/{1}", p, filename);

//	std::cout << "Saving " << fullpath << std::endl;
	lp = fullpath;

	return cv::imwrite(fullpath, img );


}
int ImageSaver::save(cv::Mat img, int arg1, std::chrono::system_clock::time_point& timestamp) {
	auto filename = fmt::format(f, count++,arg1, serializeTimePoint(timestamp,"%Y%m%d%H%M%S"));
	auto fullpath = fmt::format("{0}/{1}", p, filename );

//	std::cout << "Saving " << fullpath << std::endl;
	lp = fullpath;

	return cv::imwrite(fullpath, img );


}

std::string ImageSaver::lastPath() {
	return lp;
}

