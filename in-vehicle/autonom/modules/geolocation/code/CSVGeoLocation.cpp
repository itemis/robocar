/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 01.08.2019 Created
 */


#include "CSVGeoLocation.h"
#include "JConfig.h"

using namespace units;

extern JConfig jconfig;
CSVGeoLocation::CSVGeoLocation(const std::string& filename)  :csv(filename) {

	csv.read_header(io::ignore_extra_column,  "x", "y", "o");


}

CSVGeoLocation::~CSVGeoLocation() {
	// TODO Auto-generated destructor stub
}

int CSVGeoLocation::getLocation(millimeter_t&x, millimeter_t&y, double& orient) {
	int time;
double px, py;
	if(csv.read_row(px,py,orient)) {
		x = make_unit<millimeter_t>(px);
		y = make_unit<millimeter_t>(py);
		return 0;
	} else {
		return -1;
	}
}
