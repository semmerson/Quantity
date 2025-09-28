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

#include "AffineUnit.h"
#include "BaseInfo.h"
#include "CanonicalUnit.h"
#include "Dimensionality.h"
#include "RefLogUnit.h"
#include "UnrefLogUnit.h"

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

Unit::Pimpl Unit::get(const Pimpl& core,
                      const double slope,
                      const double intercept)
{
    return (slope == 1 && intercept == 0)
        ? core
        : Pimpl(new AffineUnit(core, slope, intercept));
}

Unit::Pimpl Unit::get(const Unit::BaseEnum base,
                      const Pimpl&        refLevel)
{
    return Pimpl(new RefLogUnit(refLevel, base));
}

Unit::Pimpl Unit::get(const Unit::BaseEnum   base,
                      const Dimensionality& dim)
{
    return Pimpl(new UnrefLogUnit(base, dim));
}

Unit::~Unit() noexcept =default;

Unit::Pimpl Unit::divideBy(const Pimpl& unit) const
{
    return multiply(unit->pow(Exponent(-1)));
}

} // namespace quantity
