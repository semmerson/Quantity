/**
 * This file implements support for units of physical quantities.
 *
 *        File: Unit.cpp
 *  Created on: Jul 31, 2025
 *      Author: Steven R. Emmerson
 *
 * Copyright 2025 Steven R. Emmerson. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 */
#include "Unit.h"

#include "BaseInfo.h"
#include "AffineUnit.h"
#include "CanonicalUnit.h"

#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

namespace quantity {

Unit::Pimpl Unit::get(const BaseInfo& baseInfo)
{
    Exponent exponent{1, 1};
    return Unit::Pimpl(new CanonicalUnit(baseInfo, exponent));
}

/**
 * Returns a possibly affine unit. An affine unit has the form "y = ax + b", where "x" is the
 * underlying unit. If the slope is one and the intercept is zero, then the underlying unit is
 * returned.
 * @param[in] core      The underlying unit
 * @param[in] slope     The slope for converting values from the @ core unit. May be one, in which
 *                      case @ core will be returned if the intercept is zero.
 * @param[in] intercept The intercept for converting values from the @ core unit. May be zero, in
 *                      which case @ core will be returned if @ slope is one.
 * @return              A new affine unit or @ core if the slope is one and the intercept is zero
 */
Unit::Pimpl Unit::get(const Pimpl& core,
                      const double slope,
                      const double intercept)
{
    return (slope == 1 && intercept == 0)
        ? core
        : Pimpl(new AffineUnit(core, slope, intercept));
}

Unit::~Unit() noexcept =default;

Unit::Pimpl Unit::divideBy(const Pimpl& unit) const
{
    return multiply(unit->pow(Exponent(-1)));
}

} // namespace quantity
