/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 25.02.2019 initial Contribution
 */


#ifndef CV_CAMERAFACTORY_H_
#define CV_CAMERAFACTORY_H_

#include "AbstractCamera.h"
#include "nlohmann/json.hpp"
using nlohmann::json;

AbstractCamera * createCamera();

json findCameraConfig();


#endif /* CV_CAMERAFACTORY_H_ */
