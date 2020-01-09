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

#ifndef CV_CVUTIL_H_
#define CV_CVUTIL_H_

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

#include "JConfig.h"
#include <string>
#include <vector>

cv::Mat buildHomography(JConfig& j , std::string src, std::string dst);
cv::Mat getHomography(JConfig& j );

std::vector<cv::Point2f> pointVectorFromJson(json array) ;
std::vector<cv::Point2f> pointVectorFromJson(json array, cv::Point2f dim);

class CVUtil {
public:
	CVUtil();
	virtual ~CVUtil();
};

#endif /* CV_CVUTIL_H_ */
