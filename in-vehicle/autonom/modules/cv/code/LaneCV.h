/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 24.02.2019 initial Contribution
 */


#ifndef CV_LANECV_H_
#define CV_LANECV_H_

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>



class LaneCV {
public:
	LaneCV();
	virtual ~LaneCV();

	cv::Mat process(cv::Mat input);
};

#endif /* CV_LANECV_H_ */
