/**
 * Copyright (c) 2019 itemis AG and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   Andreas Graf, itemis AG - 26.02.2019 initial Contribution
 */


#ifndef CV_IMAGESAVERFACTORY_H_
#define CV_IMAGESAVERFACTORY_H_


#include "AbstractImageSaver.h"

AbstractImageSaver * createImageSaver(const char * id);


#endif /* CV_IMAGESAVERFACTORY_H_ */
