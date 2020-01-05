/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 2019 initial Contribution
 */

#pragma once

#include "nlohmann/json.hpp"

#include "spdlog/logger.h"



using nlohmann::json;

/**
 * Class for handling json configuration files
 */
class JConfig {

public:
	json j;

	std::shared_ptr<spdlog::logger> logger;
public:
	JConfig();
	virtual ~JConfig();

	// Resolve dereference
	json deref(std::string jpointer);

	/** Get value of a json entry, intepret the value as a
	 * reference and deref it
	 */
	json getIndirection(std::string origVaue);

	// Load a given configuation
	void load(std::vector<std::string> filenames);

	// Load based on command line arguments
	void load(int argc, char *argv[]) ;

	// merge based on command line arguments
	void merge(int argc, char *argv[]) ;

	// merge a configuration from file into the current config
	void mergeFile(std::string fname) ;

	// merge a configuration passed as string into the current config
	void mergeFromString(std::string text);
	void setFromString(std::string text);

	// find a config file that contains the hostname and merge that
	void mergeAutomatic();
};


