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

#include "CVUtil.h"
#include <opencv2/calib3d.hpp>

#include "JsonHelper.h"
#include <vector>
#include <cmath>
#include <iostream>
using namespace cv;

CVUtil::CVUtil() {
	// TODO Auto-generated constructor stub

}

CVUtil::~CVUtil() {
	// TODO Auto-generated destructor stub
}


cv::Mat buildHomography(json j ) {
	std::vector<Point2f> src = pointVectorFromJson(j["src"] );
	std::vector<Point2f> dst = pointVectorFromJson(j["dst"]);


	std::cout<< src << std::endl;
	std::cout <<dst << std::endl;


	return findHomography(src,dst);
}

cv::Mat getHomography(JConfig& jconfig ) {
	auto homographyConfig = jconfig.getIndirection("homography");
	std::cout << homographyConfig << std::endl;
	if(homographyConfig.contains("direct")) {
		auto homographyMat = Mat_<double>(3,3);
		matrixFromJson(homographyMat, homographyConfig["direct"]);
		std::cout << "Loaded Matrix direct" <<std::endl;
		std::cout << homographyMat << std::endl;
		return homographyMat;
	} else {
		std::cout << "Calculated Matrix" <<std::endl;
		return buildHomography(homographyConfig);
	}

}
std::vector<Point2f> pointVectorFromJson(json array) {
	std::vector<Point2f> result;
	for(int i = 0; i< 4; i++) {


		result.push_back(Point2f(array[i][0].get<double>(),array[i][1].get<double>()));
	}
    return result;
}

std::vector<Point2f> pointVectorFromJson(json array, Point2f dim) {
	std::vector<Point2f> result;
	for(int i = 0; i< array.size(); i++) {

		auto x = array[i][0].get<double>();
		auto y = array[i][1].get<double>();

		Point2f e(std::signbit(x) ? dim.x - x : x, std::signbit(y) ? dim.y - y  : y);

		result.push_back(e);
	}
    return result;
}

