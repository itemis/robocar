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


#ifndef FIXEDGEOLOCATION_H_
#define FIXEDGEOLOCATION_H_

#include "AbstractGeolocation.h"

using namespace units::angle;

class FixedGeolocation: public AbstractGeolocation {
	millimeter_t ix,iy;
	degree_t iorient;
public:
	FixedGeolocation(millimeter_t x, millimeter_t y, degree_t orient);
	virtual ~FixedGeolocation();

	virtual int getLocation(millimeter_t&x, millimeter_t&y, double& orient) ;
};

#endif /* FIXEDGEOLOCATION_H_ */
