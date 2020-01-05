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


#include "GeoLocationFactory.h"
#include "JConfig.h"
#include "MMGeoLocation.h"
#include "CSVGeoLocation.h"
#include "FixedGeolocation.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace units::angle;
using namespace units;


extern JConfig jconfig;
AbstractGeolocation * createGeolocation() {
	auto static logger = spdlog::stderr_color_mt("geolocation-factory-c");

	// The geolocation value holds a reference to the actual values
	//
	std::string  georef = jconfig.j["geolocation"].get<std::string>();

	logger->info("Configured geolocation: {0}", georef);

	auto geodef = jconfig.deref(georef);



	if(geodef["type"].get<std::string>().compare("marvelmind")==0) {
		return new MMGeoLocation();
	}

	if(geodef["type"].get<std::string>().compare("csv")==0) {
		return new CSVGeoLocation(geodef["file"].get<std::string>());
	}

	if(geodef["type"].get<std::string>().compare("fixed")==0) {
		millimeter_t x = make_unit<millimeter_t>(geodef["x"].get<double>());
		millimeter_t y = make_unit<millimeter_t>(geodef["y"].get<double>());
		degree_t o = make_unit<degree_t>(geodef["orientation"].get<double>());

		return new FixedGeolocation(x,y,o);
	}


	logger->error("Undefined geolocation type");

}
