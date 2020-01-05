/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 2019
 */


#include "FixedGeolocation.h"
using namespace units::angle;

FixedGeolocation::FixedGeolocation(millimeter_t x, millimeter_t y, degree_t orient)   {
	ix = x;
	iy = y;
	iorient = orient;
}

FixedGeolocation::~FixedGeolocation() {

}

int FixedGeolocation::getLocation(millimeter_t&x, millimeter_t&y, double& orient) {
	x = ix;
	y = iy;
	orient = iorient.value();

	return 0 ;
}
