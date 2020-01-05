/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 18.08.2019 Created
 */


#ifndef CSVGEOLOCATION_H_
#define CSVGEOLOCATION_H_

#include "AbstractGeolocation.h"
#include "csv.h"



class CSVGeoLocation: public AbstractGeolocation {
	io::CSVReader<3> csv;

public:
	CSVGeoLocation(const std::string& filename);
	virtual ~CSVGeoLocation();

	int getLocation(millimeter_t&x, millimeter_t&y, double& orient) ;
};

#endif /* CSVGEOLOCATION_H_ */
