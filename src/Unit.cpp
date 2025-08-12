/**
 * This file implements a class for units of physical quantities.
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
    return pImpl->isConvertible(*other.pImpl.get());
}

Unit Unit::multiply(const Unit& unit) const
{
    return Unit(pImpl->multiply(unit.pImpl.get()));
}

#if 0
Unit Unit::divideBy(const double factor) const
{
    return pImpl->divideBy(pImpl->divideBy(factor));
}

Unit Unit::divideBy(const Unit& unit) const
{
    return Unit(pImpl->divideBy(unit.pImpl.get()));
}

Unit Unit::pow(const int power) const
{
    return Unit(pImpl->pow(power));
}

Unit Unit::root(const int root) const
{
    return Unit(pImpl->root(root));
}
#endif

double Unit::convert(const double value) const
{
    return pImpl->convert(value);
}

} // Namespace
