/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 16.09.2019 Created
 */

#include "MMGeoLocation.h"
#include "catch2/single_include/catch2/catch.hpp"
#include "JConfig.h"

#include <chrono>
#include <thread>

#include <iostream>

JConfig jconfig;

TEST_CASE( "MMGeoLocation", "[geoloc]" ) {
	JConfig jconfig;
	MMGeoLocation sut ;
    SECTION("testMMGeoLocation")
    {
    	double o;
	millimeter_t x,y;
    	for(int i = 0; i< 10; i++) {
		sut.getLocation(x,y,o);
    		std::cout << to_string(x) << ", " << to_string(y) << ", " << o << std::endl;
    		sleep(1);
    	}

    }



}
