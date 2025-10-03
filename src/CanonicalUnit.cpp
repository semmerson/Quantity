/**
 * This file implements canonical units of physical quantities.
 *
 *        File: CanonicalUnit.cpp
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
#include "CanonicalUnit.h"

#include "AffineUnit.h"
#include "BaseInfo.h"
#include "ConverterImpl.h"
#include "Exponent.h"
#include "RefLogUnit.h"
#include "UnrefLogUnit.h"

namespace quantity {

/// A unit value converter that returns the same value.
class TrivialConverter final : public ConverterImpl
{
public:
    /**
     * Converts a numeric value in the input unit to the equivalent value in the output unit.
     * @param[in] value     Numeric value in the input unit
     * @return              Equivalent value in the output unit
     */
    double operator()(const double value) const override
    {
        return value;
    }
};

CanonicalUnit::CanonicalUnit(const UnitFactors& otherFactors)
    : factors(otherFactors)
{}

CanonicalUnit::CanonicalUnit(const BaseInfo& baseInfo,
                             Exponent        exp)
    : factors{UnitFactor(baseInfo, exp)}
{}

CanonicalUnit::CanonicalUnit(const BaseInfo& baseInfo)
    : CanonicalUnit(baseInfo, Exponent(1, 1))
{}

std::string CanonicalUnit::to_string() const
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

Unit::Type CanonicalUnit::type() const
{
    return (factors.size() == 1 && factors.begin()->second.isOne())
            ? Type::BASE
            : Type::CANONICAL;
}

bool CanonicalUnit::isDimensionless() const
{
    return factors.size() == 0;
}

bool CanonicalUnit::isOffset() const
{
    return false;   // The origin of a derived unit is always zero
}

size_t CanonicalUnit::hash() const
{
    size_t hash = 0;
    for (const auto& factor : factors)
        hash ^= factor.first.hash() ^ factor.second.hash();
    return hash;
}

int CanonicalUnit::compare(const Pimpl& other) const
{
    return -other->compareTo(*this);
}

int CanonicalUnit::compareTo(const CanonicalUnit& other) const
{
    auto       iter1 = factors.begin();
    const auto end1 = factors.end();
    auto       iter2 = other.factors.begin();
    const auto end2 = other.factors.end();

    while (iter1 != end1 && iter2 != end2) {
        auto cmp = iter1->first.compare(iter2->first);      // Primary sort on base units
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

int CanonicalUnit::compareTo(const AffineUnit& other) const
{
    return -1;  // Canonical units come before everything else
}

int CanonicalUnit::compareTo(const RefLogUnit& other) const
{
    return -1;  // Canonical units come before everything else
}

int CanonicalUnit::compareTo(const UnrefLogUnit& other) const
{
    return -1;  // Canonical units come before everything else
}

bool CanonicalUnit::isConvertible(const Pimpl& other) const
{
    return other->isConvertibleTo(*this);
}

bool CanonicalUnit::isConvertibleTo(const CanonicalUnit& other) const
{
    if (factors.size() != other.factors.size())
        return false;

    auto       iter1 = factors.begin();
    auto       iter2 = other.factors.begin();
    const auto end1 = factors.end();

    for (; iter1 != end1; ++iter1, ++iter2)
        if (iter1->first.compare(iter2->first) != 0 || iter1->second.compare(iter2->second) != 0)
            return false;

    return true;
}

bool CanonicalUnit::isConvertibleTo(const AffineUnit& other) const
{
    return other.isConvertibleTo(*this); // Defer to the other unit
}

bool CanonicalUnit::isConvertibleTo(const RefLogUnit& other) const
{
    return other.isConvertibleTo(*this); // Defer to the other unit
}

bool CanonicalUnit::isConvertibleTo(const UnrefLogUnit& other) const
{
    return other.isConvertibleTo(*this); // Defer to the other unit
}

Converter CanonicalUnit::getConverterTo(const Pimpl& output) const
{
    return output->getConverterFrom(*this);
}

Converter CanonicalUnit::getConverterFrom(const CanonicalUnit& output) const
{
    if (!isConvertibleTo(output))
        throw invalid_argument("Units are not convertible");

    return Converter(new TrivialConverter());
}

Converter CanonicalUnit::getConverterFrom(const AffineUnit& output) const
{
    throw logic_error("CanonicalUnit::getConverterFrom(AffineUnit) shouldn't be called");
}

Converter CanonicalUnit::getConverterFrom(const RefLogUnit& output) const
{
    //output.getConverterTo
    throw logic_error("CanonicalUnit::getConverterFrom(RefLogUnit) shouldn't be called");
}

Converter CanonicalUnit::getConverterFrom(const UnrefLogUnit& output) const
{
    //output.getConverterTo
    throw logic_error("CanonicalUnit::getConverterFrom(UnrefLogUnit) shouldn't be called");
}

CanonicalUnit::Pimpl CanonicalUnit::multiply(const Pimpl& other) const
{
    return other->multiplyBy(*this);
}

Unit::Pimpl CanonicalUnit::multiplyBy(const CanonicalUnit& other) const
{
    const CanonicalUnit* smaller;
    const CanonicalUnit* larger;
    if (factors.size() <= other.factors.size()) {
        smaller = this;
        larger = &other;
    }
    else {
        larger = this;
        smaller = &other;
    }

    auto newImpl = new CanonicalUnit(*larger);

    for (const auto& factor : smaller->factors) {
        auto iter = newImpl->factors.find(factor.first);
        if (iter == newImpl->factors.end()) {
            newImpl->factors.insert(factor);
        }
        else {
            iter->second = iter->second.add(factor.second);
        }
    }

    return Pimpl(newImpl);
}

Unit::Pimpl CanonicalUnit::multiplyBy(const AffineUnit& other) const
{
    return other.multiplyBy(*this); // Defer to the affine unit
}

Unit::Pimpl CanonicalUnit::pow(const Exponent exp) const
{
    auto newImpl = new CanonicalUnit(*this);

    for (auto& factor : newImpl->factors)
        factor.second = factor.second.multiply(exp);

    return Pimpl(newImpl);
}

} // Namespace
