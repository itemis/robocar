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


#include "TimedCSVGeoLocation.h"
#include "JConfig.h"

extern JConfig jconfig;
using namespace std::chrono;
using namespace units;

TimedCSVGeoLocation::TimedCSVGeoLocation(const std::string& filename, int ms) :csv(filename) , ms(ms),
		tstamp(duration_cast< milliseconds >(
			    system_clock::now().time_since_epoch()
			)),co(0), cx(0), cy(0) {
	csv.read_header(io::ignore_extra_column,  "x", "y", "o");
	csv.read_row(cx,cy,co);
}

TimedCSVGeoLocation::~TimedCSVGeoLocation() {
	// TODO Auto-generated destructor stub
}

int TimedCSVGeoLocation::getLocation(millimeter_t&x, millimeter_t&y, double& orient) {
	milliseconds time_now = duration_cast< milliseconds >(
		    system_clock::now().time_since_epoch()
		);

	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - tstamp).count();

	if(elapsed >= ms) {
		tstamp = time_now;
		if(csv.read_row(cx,cy,co)) {

			} else {
				return -1;
			}
	}

	x = make_unit<millimeter_t>(cx);
	y = make_unit<millimeter_t>(cy);
	orient = co;

	return 0;


}
