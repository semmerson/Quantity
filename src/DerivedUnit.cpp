/**
 * This file implements a derived unit of a physical quantity.
 *
 *        File: DerivedUnit.cpp
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

#include "DerivedUnit.h"

#include "AffineUnit.h"
#include "BaseUnit.h"
#include "Exponent.h"

namespace quantity {

DerivedUnit::DerivedUnit(const UnitFactors& otherFactors)
    : factors(otherFactors)
{}

DerivedUnit::DerivedUnit(const BaseUnit& base,
                         Exponent        exp)
    : DerivedUnit()
{
    factors.insert(UnitFactor(base, exp));
}

DerivedUnit::DerivedUnit(const BaseUnit& base)
    : DerivedUnit(base, Exponent(1, 1))
{}

std::string DerivedUnit::to_string() const
{
    string rep{""};
    bool   haveFactor = false;

    for (const auto& factor : factors) {
        if (haveFactor)
            rep += "·";
        rep += factor.first.to_string();
        if (!factor.second.isOne())
            rep += "^" + factor.second.to_string();
        haveFactor = true;
    }

    return rep;
}

/**
 * Indicates the type of this unit.
 * @return The type of this unit
 */
Unit::UnitType DerivedUnit::type() const
{
    return UnitType::derived;
}

bool DerivedUnit::isBase() const
{
    return factors.size() == 1 && factors.begin()->second.isOne();
}

bool DerivedUnit::isDimensionless() const
{
    return factors.size() == 0;
}

bool DerivedUnit::isOffset() const
{
    return false;   // The origin of a derived unit is zero
}

size_t DerivedUnit::hash() const
{
    size_t hash = 0;
    for (const auto& factor : factors)
        hash ^= factor.first.hash() ^ factor.second.hash();
    return hash;
}

int DerivedUnit::compare(const Pimpl& other) const
{
    return -other->compareTo(*this);
}

bool DerivedUnit::isConvertible(const Pimpl& other) const
{
    return other->isConvertibleTo(*this);
}

double DerivedUnit::convertTo(const double value) const
{
    return value;
}

DerivedUnit::Pimpl DerivedUnit::multiply(const Pimpl& other) const
{
    return other->multiplyBy(*this);
}

int DerivedUnit::compareTo(const BaseUnit& other) const
{
    return 1; // Derived units come after base units
}

int DerivedUnit::compareTo(const DerivedUnit& other) const
{
    auto       iter1 = factors.begin();
    const auto end1 = factors.end();
    auto       iter2 = other.factors.begin();
    const auto end2 = other.factors.end();

    while (iter1 != end1 && iter2 != end2) {
        auto cmp = iter1->first.compareTo(iter2->first);    // Primary sort on base units
        if (cmp)
            return cmp;
        cmp = iter1->second.compare(iter2->second);         // Secondary sort on exponents
        if (cmp)
            return cmp;
        ++iter1;
        ++iter2;
    }

    return (iter1 == end1 && iter2 == end2)                 // Tertiary sort on length
            ? 0
            : iter1 == end1
              ? -1
              : 1;
}

int DerivedUnit::compareTo(const AffineUnit& other) const
{
    return -1;  // Derived units come before affine units
}

bool DerivedUnit::isConvertibleTo(const BaseUnit& other) const
{
    if (factors.size() != 1)
        return false;

    const auto iter = factors.begin();

    return iter->first.compareTo(other) == 0 && iter->second.isOne();
}

bool DerivedUnit::isConvertibleTo(const DerivedUnit& other) const
{
    if (factors.size() != other.factors.size())
        return false;

    auto       iter1 = factors.begin();
    auto       iter2 = other.factors.begin();
    const auto end1 = factors.end();

    for (; iter1 != end1; ++iter1, ++iter2)
        if (iter1->first.compareTo(iter2->first) != 0 || iter1->second.compare(iter2->second) != 0)
            return false;

    return true;
}

bool DerivedUnit::isConvertibleTo(const AffineUnit& other) const
{
    return other.isConvertibleTo(*this); // Defer to the affine unit
}

Unit::Pimpl DerivedUnit::multiplyBy(const BaseUnit& baseUnit) const
{
    return multiplyBy(DerivedUnit(baseUnit));
}

Unit::Pimpl DerivedUnit::multiplyBy(const DerivedUnit& other) const
{
    UnitFactors newFactors(factors);

    for (const auto& otherFactor : other.factors) {
        auto iter = newFactors.find(otherFactor.first); // Find same base unit
        if (iter == newFactors.end()) {
            newFactors.insert(otherFactor);             // Insert if doesn't exit
        }
        else {
            iter->second.add(otherFactor.second);       // Add exponents of base units
            if (iter->second.isZero())
                newFactors.erase(iter);                 // Delete dimensionless unit one factor
        }
    }

    return Pimpl(new DerivedUnit(newFactors));
}

Unit::Pimpl DerivedUnit::multiplyBy(const AffineUnit& other) const
{
    return other.multiplyBy(*this); // Defer to the affine unit
}

} // Namespace
