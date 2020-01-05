/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 16.08.2019 Created
 */


#include "MMGeoLocation.h"
#include <cmath>
MMGeoLocation::MMGeoLocation() {
	// TODO Auto-generated constructor stub

}

MMGeoLocation::~MMGeoLocation() {
	// TODO Auto-generated destructor stub
}

int MMGeoLocation::getLocation(millimeter_t&x, millimeter_t&y, double& orient) {
	return mm.getLocation(x,y,orient);
}

bool  MMGeoLocation::isPlausible(millimeter_t&x, millimeter_t&y) {
	return std::abs(y.value()) < 1000000000 && std::abs(x.value()) < 1000000000;
}
