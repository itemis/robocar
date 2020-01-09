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


#ifndef CV_STREAMER_H_
#define CV_STREAMER_H_

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

#include "JConfig.h"
#include <string>
#include <iostream>
class Streamer {
	bool is_init = false;

	void lazy_init(cv::Mat& img);
	int p_fd1[2];
	std::ostream *os=nullptr;
public:
	Streamer();
	virtual ~Streamer();

	virtual void stream(cv::Mat& img);
};

#endif /* CV_STREAMER_H_ */
