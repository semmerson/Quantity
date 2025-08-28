/**
 * This file implements support for units of physical quantities.
 *
 *        File: Unit.cpp
 *  Created on: Aug 3, 2025
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

#include "Unit.h"
#include "UnitImpl.h"

namespace quantity {

Unit::Unit(UnitImpl* impl)
    : pImpl(impl)
{}

Unit& Unit::operator=(const Unit& rhs)
{
    pImpl = rhs.pImpl;
    return *this;
}

Unit::operator bool() const noexcept
{
    return static_cast<bool>(pImpl);
}

size_t Unit::hash() const
{
    return pImpl->hash();
}

int Unit::compare(const Unit& other) const
{
    return pImpl->compare(*other.pImpl);
}

std::string Unit::to_string() const
{
    return pImpl->to_string();
}

bool Unit::isDimensionless() const
{
    return pImpl->isDimensionless();
}

bool Unit::isOffset() const
{
    return pImpl->isOffset();
}

bool Unit::isConvertible(const Unit& other) const
{
    return pImpl->isConvertible(*other.pImpl);
}

Unit Unit::multiply(const Unit& unit) const
{
    return Unit(pImpl->multiply(*unit.pImpl));
}

double Unit::convert(const double value) const
{
    return pImpl->convert(value);
}

BaseUnit::BaseUnit(
        const string&  name,
        const string&  symbol)
    : Unit(new BaseUnitImpl(name, symbol))
{}

AffineUnit::AffineUnit(
        const Unit&     core,
        const double    slope,
        const double    intercept)
    : Unit(new AffineUnitImpl(*core.pImpl, slope, intercept))
{}

} // Namespace
