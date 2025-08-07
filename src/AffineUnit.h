/**
 * This file declares an affine unit (i.e., one with a "y=ax+b" scale-transform).
 *
 *        File: AffineUnit.h
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

#pragma once

#include "Unit.h"

namespace quantity {

/// Declaration of an affine unit.
class AffineUnit : public Unit
{
public:
    /**
     * Constructs.
     * @param[in] core          The underlying unit
     * @param[in] slope         The slope
     * @param[in] intercept     The intercept
     */
    AffineUnit(
            const Unit&     core,
            const double    slope,
            const double    intercept);
};

}
