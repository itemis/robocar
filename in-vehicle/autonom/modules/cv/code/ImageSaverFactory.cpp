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


#include "ImageSaverFactory.h"
#include "ImageSaver.h"
#include "JConfig.h"

#include <iostream>
#include <string>

extern JConfig jconfig;


AbstractImageSaver * createImageSaver(const char * id) {
	auto config = (jconfig.j)[id];
	if(config.empty())
		return nullptr;

	auto p = config["path"].get<std::string>();
	auto f = config["file"].get<std::string>();

//	std::cout << "F " << p << " " <<f << std::endl;

	AbstractImageSaver * result = new ImageSaver(p,f );



	return result;
}
