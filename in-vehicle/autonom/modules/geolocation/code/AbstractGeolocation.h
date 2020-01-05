/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 01.07.2019 Created
 */

#ifndef ABSTRACTGEOLOCATION_H_
#define ABSTRACTGEOLOCATION_H_

#include <units.h>

using namespace units::literals;
using namespace units::length;

/**
 * Interface for the geo location.
 */
class AbstractGeolocation {
public:
	AbstractGeolocation();
	virtual ~AbstractGeolocation();

	/**
	 * Get current position and orientation.
	 */
	virtual int getLocation(millimeter_t&x, millimeter_t&y, double& orient) = 0;

	/**
	 * Check if values are actually plausible.
	 *
	 */
	virtual bool isPlausible(millimeter_t&x, millimeter_t&y) {
		return true;
	}

};

#endif /* ABSTRACTGEOLOCATION_H_ */
