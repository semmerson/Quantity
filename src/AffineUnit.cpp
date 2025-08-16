/**
 * This file defines an affine unit of a physical quantity.  The scale-transform of an affine unit
 * has the form "y=ax+b".
 *
 *        File: AffineUnit.cpp
 *  Created on: Jul 27, 2025
 *      Author: Steven R. Emmerson
 *
 * Copyright 2025 Steven R. Emmerson. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "AffineUnit.h"

#include "AffineUnitImpl.h"

namespace quantity {

AffineUnit::AffineUnit(
        const Unit&     core,
        const double    slope,
        const double    intercept)
    : Unit(new AffineUnitImpl(*core.pImpl, slope, intercept))
{}

} // namespace
