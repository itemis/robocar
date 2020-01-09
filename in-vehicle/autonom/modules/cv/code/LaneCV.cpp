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


#include "LaneCV.h"
#include <iostream>
using namespace cv;
using namespace std;

const int width = 320;

const int max_value_H = 360/2;
const int max_value = 255;

const int low_H = 0, low_S = 0, low_V = (max_value*7)/10;
int high_H = max_value_H, high_S = max_value/5, high_V = max_value;

LaneCV::LaneCV() {
	// TODO Auto-generated constructor stub

}

LaneCV::~LaneCV() {
	// TODO Auto-generated destructor stub
}

Mat LaneCV::process(Mat input) {
	Mat dst;

	double fac = (double)320 / input.size().width;
	resize(input,dst,Size(),fac,fac,INTER_AREA);

	Rect crop(0, dst.size().height/3 ,dst.size().width, (2*dst.size().height)/3);

	Mat roi = dst(crop);

//	Mat hsv;
//	cout << "Convert" << endl;
//	cvtColor(roi, hsv, COLOR_BGR2HSV,3);
	Mat threshold;
//	cout << "Thresh" << endl;
//	inRange(hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), threshold);

	Mat gry;
	cvtColor(roi,gry, COLOR_BGR2GRAY);
	inRange(gry, Scalar(200),Scalar(255), threshold);

	Mat bgr;
//	cout << "Convert" << endl;
//	cvtColor(threshold, bgr, COLOR_HSV2BGR,0);

	return threshold;
}
