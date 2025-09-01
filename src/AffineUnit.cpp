/**
 * This file implements an affine unit of a physical quantity.
 *
 *        File: AffineUnit.h
 *  Created on: Aug 29, 2025
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

#include "BaseUnit.h"
#include "DerivedUnit.h"

namespace quantity {

AffineUnit::AffineUnit(
        const Pimpl&      core,
        const double      slope,
        const double      intercept)
    : core{core}
    , slope{slope}
    , intercept{intercept}
{
    if (slope == 0)
        throw std::invalid_argument("Slope is zero");
}

std::string AffineUnit::to_string() const
{
    string rep{""};
    if (slope != 1) {
        rep += std::to_string(slope) + "*";
    }
    string coreStr = core->to_string();
    const bool haveBlank = coreStr.find(" ") != string::npos;
    if (haveBlank)
        rep += "(";
    rep += coreStr;
    if (haveBlank)
        rep += ")";
    if (intercept < 0) {
        rep += " - " + std::to_string(abs(intercept));
    }
    else if (intercept > 0) {
        rep += " + " + std::to_string(intercept);
    }
    return rep;
}

/**
 * Indicates if this instance is a base unit (e.g., meter).
 * @retval true  This instance is a base unit
 * @retval false This instance is not a base unit
 */
bool AffineUnit::isBase() const
{
    return slope == 1 && intercept == 0 && core->isBase();
}

bool AffineUnit::isDimensionless() const
{
    return core->isDimensionless();
}

bool AffineUnit::isOffset() const
{
    return intercept != 0;
}

size_t AffineUnit::hash() const
{
    static auto myHash = std::hash<double>();
    return core->hash() ^ myHash(slope) ^ myHash(intercept);
}

int AffineUnit::compare(const Pimpl& other) const
{
    return -other->compareTo(*this);
}

bool AffineUnit::isConvertible(const Pimpl& other) const
{
    return other->isConvertibleTo(*this);
}

double AffineUnit::convertDown(const double value) const
{
    return value * slope + intercept;
}

Unit::Pimpl AffineUnit::multiply(const Pimpl& other) const
{
    return other->multiplyBy(*this);
}

int AffineUnit::compareTo(const BaseUnit& other) const
{
    return 1;   // Affine units come after base units
}

int AffineUnit::compareTo(const DerivedUnit& other) const
{
    return 1;   // Affine units come after derived units
}

int AffineUnit::compareTo(const AffineUnit& other) const
{
    int cmp = core->compare(other.core);
    if (cmp != 0)
        return cmp;
    cmp = slope < other.slope
            ? -1
            : slope > other.slope
              ? 1
              : 0;
    if (cmp != 0)
        return cmp;
    return intercept < other.intercept
            ? -1
            : intercept > other.intercept
              ? 1
              : 0;
}

bool AffineUnit::isConvertibleTo(const BaseUnit& other) const
{
    return core->isConvertibleTo(other);
}

bool AffineUnit::isConvertibleTo(const DerivedUnit& other) const
{
    return core->isConvertibleTo(other);
}

bool AffineUnit::isConvertibleTo(const AffineUnit& other) const
{
    return core->isConvertible(other.core);
}

Unit::Pimpl AffineUnit::multiplyBy(const BaseUnit& other) const
{
    if (intercept != 0)
        throw std::logic_error("Multiplication by an offset unit isn't supported");

    auto newCore = core->multiplyBy(other);
    return slope == 1
            ? newCore
            : Unit::Pimpl(new AffineUnit(newCore, slope, 0));
}

Unit::Pimpl AffineUnit::multiplyBy(const DerivedUnit& other) const
{
    if (intercept != 0)
        throw std::logic_error("Multiplication by an offset unit isn't supported");

    auto newCore = core->multiplyBy(other);
    return slope == 1
            ? newCore
            : make_shared<AffineUnit>(newCore, slope, 0);
}

Unit::Pimpl AffineUnit::multiplyBy(const AffineUnit& other) const
{
    if (intercept != 0 || other.intercept != 0)
        throw std::logic_error("Multiplication by an offset unit isn't supported");

    Pimpl newCore = core->multiply(other.core);
    const auto newSlope = slope*other.slope;
    return newSlope == 1
            ? newCore
            : make_shared<AffineUnit>(newCore, newSlope, 0);
}

} // Namespace
