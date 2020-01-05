/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 30.09.2019 Created
 */


#pragma once

#include "AbstractGeolocation.h"
#include "csv.h"

#include <chrono>

class TimedCSVGeoLocation  : public AbstractGeolocation{
	io::CSVReader<3> csv;
	int ms;
	double cx, cy, co;
	std::chrono::milliseconds tstamp;

public:
	TimedCSVGeoLocation(const std::string& filename, int ms);
	virtual ~TimedCSVGeoLocation();

	int getLocation(millimeter_t&x, millimeter_t&y, double& orient) ;
};


