/**
 * This file implements units of physical quantities.
 *
 *        File: UnitImpl.cpp
 *  Created on: Aug 22, 2025
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

#include "UnitImpl.h"

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>

using namespace std;

namespace quantity {

UnitImpl::~UnitImpl()
{}

BaseUnitImpl::BaseUnitImpl()
    : name{""}
    , symbol{""}
{}

BaseUnitImpl::BaseUnitImpl(const std::string&  name,
                           const std::string&  symbol)
    : name(name)
    , symbol(symbol)
{
    if (name.size() == 0)
        throw invalid_argument("Empty base unit name");
    if (symbol.size() == 0)
        throw invalid_argument("Empty base unit symbol");

    if (!nameSet.insert(name).second)
        throw invalid_argument("Base unit \"" + name + "\" already exists");
    if (!symSet.insert(symbol).second)
        throw invalid_argument("Base unit \"" + symbol + "\" already exists");
}

BaseUnitImpl::~BaseUnitImpl() noexcept
{
    nameSet.erase(name);
    symSet.erase(symbol);
}

std::string BaseUnitImpl::to_string() const
{
    return symbol;
}

bool BaseUnitImpl::isDimensionless() const
{
    return false;
}

bool BaseUnitImpl::isOffset() const
{
    return false;
}

size_t BaseUnitImpl::hash() const
{
    static auto myHash = std::hash<string>();
    return myHash(name);
}

int BaseUnitImpl::compare(const UnitImpl& other) const
{
    return -other.compareTo(*this);
}

int BaseUnitImpl::compareTo(const BaseUnitImpl& other) const
{
    return name.compare(other.name);
}

int BaseUnitImpl::compareTo(const DerivedUnitImpl& other) const
{
    return -1;  // Base units always come before derived units
}

int BaseUnitImpl::compareTo(const AffineUnitImpl& other) const
{
    return -1;  // Base units always come before affine units
}

bool BaseUnitImpl::isConvertible(const UnitImpl& other) const
{
    return other.isConvertibleTo(*this);
}

bool BaseUnitImpl::isConvertibleTo(const BaseUnitImpl& other) const
{
    return this == &other; // There can be only one!
}

bool BaseUnitImpl::isConvertibleTo(const DerivedUnitImpl& other) const
{
    return other.isConvertibleTo(*this); // Defer to the affine unit
}

bool BaseUnitImpl::isConvertibleTo(const AffineUnitImpl& other) const
{
    return other.isConvertibleTo(*this); // Defer to the affine unit
}

double BaseUnitImpl::convert(const double value) const
{
    return value;
}

UnitImpl* BaseUnitImpl::multiply(const UnitImpl& unit) const
{
    return unit.multiplyBy(*this);
}

UnitImpl* BaseUnitImpl::multiplyBy(const BaseUnitImpl& other) const
{
    return DerivedUnitImpl(*this).multiplyBy(other);
}

UnitImpl* BaseUnitImpl::multiplyBy(const DerivedUnitImpl& other) const
{
    return other.multiplyBy(*this);
}

UnitImpl* BaseUnitImpl::multiplyBy(const AffineUnitImpl& other) const
{
    return other.multiplyBy(*this);
}

unordered_set<string>    BaseUnitImpl::nameSet(7);    ///< Set of extant base unit names
unordered_set<string>    BaseUnitImpl::symSet(7);     ///< Set of extant base unit symbols

/**************************************************************************************************/

DerivedUnitImpl::DerivedUnitImpl(const UnitFactor& factor)
    : DerivedUnitImpl()
{
    if (!factor.isOne())
        factors.insert(factor);
}

DerivedUnitImpl::DerivedUnitImpl(const UnitFactors& otherFactors)
    : DerivedUnitImpl()
{
    for (const auto factor : otherFactors)
        if (!factor.isOne())
            factors.insert(factor);
}

DerivedUnitImpl::DerivedUnitImpl(const BaseUnitImpl& base,
                                 const Exponent&     exp)
    : DerivedUnitImpl(UnitFactor(base, exp))
{}

std::string DerivedUnitImpl::to_string() const
{
    string rep{""};
    bool   haveFactor = false;

    for (const auto& factor : factors) {
        if (haveFactor)
            rep += "·";
        rep += factor.baseUnit.to_string();
        if (!factor.exponent.isUnity()) {
            rep += "^";
            rep += factor.exponent.to_string();
        }
        haveFactor = true;
    }

    return rep;
}

bool DerivedUnitImpl::isDimensionless() const
{
    return factors.size() == 0;
}

bool DerivedUnitImpl::isOffset() const
{
    return false;   // Derived units have a zero origin
}

size_t DerivedUnitImpl::hash() const
{
    size_t hash = 0;
    for (const auto& factor : factors)
        hash ^= factor.baseUnit.hash() ^ factor.exponent.hash();
    return hash;
}

int DerivedUnitImpl::compare(const UnitImpl& other) const
{
    return -other.compareTo(*this);
}

int DerivedUnitImpl::compareTo(const BaseUnitImpl& other) const
{
    return 1; // Derived units come after base units
}

int DerivedUnitImpl::compareTo(const DerivedUnitImpl& other) const
{
    auto       iter1 = factors.begin();
    const auto end1 = factors.end();
    auto       iter2 = other.factors.begin();
    const auto end2 = other.factors.end();

    while (iter1 != end1 && iter2 != end2) {
        auto cmp = iter1->baseUnit.compare(iter2->baseUnit);  // Primary sort on base unit
        if (cmp)
            return cmp;
        cmp = iter1->exponent.compare(iter2->exponent);         // Secondary sort on exponent
        if (cmp)
            return cmp;
        ++iter1;
        ++iter2;
    }

    const auto s1 = factors.size();
    const auto s2 = other.factors.size();
    return (s1 < s2)                                            // Tertiary sort on size
            ? -1
            : (s1 == s2)
              ? 0
              : 1;
}

int DerivedUnitImpl::compareTo(const AffineUnitImpl& other) const
{
    return -1;  // Derived units come before affine units
}

bool DerivedUnitImpl::isConvertible(const UnitImpl& other) const
{
    return other.isConvertibleTo(*this);
}

bool DerivedUnitImpl::isConvertibleTo(const BaseUnitImpl& other) const
{
    if (factors.size() != 1)
        return false;

    const auto iter = factors.begin();

    return iter->baseUnit.compareTo(other) == 0 && iter->exponent.isUnity();
}

bool DerivedUnitImpl::isConvertibleTo(const DerivedUnitImpl& other) const
{
    if (factors.size() != other.factors.size())
        return false;

    auto       iter1 = factors.begin();
    auto       iter2 = other.factors.begin();
    const auto end1 = factors.end();

    for (; iter1 != end1; ++iter1, ++iter2)
        if (iter1->baseUnit.compareTo(iter2->baseUnit) != 0
                || iter1->exponent.compare(iter2->exponent) != 0)
            return false;

    return true;
}

bool DerivedUnitImpl::isConvertibleTo(const AffineUnitImpl& other) const
{
    return other.isConvertibleTo(*this); // Defer to the affine unit
}

double DerivedUnitImpl::convert(const double value) const
{
    return value;
}

UnitImpl* DerivedUnitImpl::multiply(const UnitImpl& other) const
{
    return other.multiplyBy(*this);
}

UnitImpl* DerivedUnitImpl::multiplyBy(const BaseUnitImpl& other) const
{
    const UnitFactor  factor(other);
    UnitFactors       newFactors(factors);
    auto              iter = newFactors.find(factor);

    if (iter == newFactors.end()) {
        newFactors.insert(factor);
    }
    else {
        iter->exponent.add(Exponent());
    }
    return new DerivedUnitImpl(newFactors);
}

UnitImpl* DerivedUnitImpl::multiplyBy(const DerivedUnitImpl& other) const
{
    UnitFactors newFactors(factors);

    for (const auto& otherFactor : other.factors) {
        auto iter = newFactors.find(otherFactor);
        if (iter == newFactors.end()) {
            newFactors.insert(otherFactor);
        }
        else {
            iter->exponent.add(otherFactor.exponent);
        }
    }

    return new DerivedUnitImpl(newFactors);
}

UnitImpl* DerivedUnitImpl::multiplyBy(const AffineUnitImpl& other) const
{
    return other.multiplyBy(*this);
}

/**************************************************************************************************/

AffineUnitImpl::AffineUnitImpl(
        const UnitImpl&   core,
        const double      slope,
        const double      intercept)
    : core(core)
    , slope(slope)
    , intercept(intercept)
{
    if (slope == 0)
        throw std::invalid_argument("The slope is zero");
}

std::string AffineUnitImpl::to_string() const
{
    string rep{""};
    if (slope != 1) {
        rep += std::to_string(slope) + "*";
    }
    string coreStr = core.to_string();
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

bool AffineUnitImpl::isDimensionless() const
{
    return core.isDimensionless();
}

bool AffineUnitImpl::isOffset() const
{
    return intercept != 0;
}

size_t AffineUnitImpl::hash() const
{
    static const auto myHash = std::hash<double>();
    return core.hash() ^ myHash(slope) ^ myHash(intercept);
}

int AffineUnitImpl::compare(const UnitImpl& other) const
{
    return -other.compareTo(*this);
}

int AffineUnitImpl::compareTo(const BaseUnitImpl& other) const
{
    return 1;   // Affine units come after base units
}

int AffineUnitImpl::compareTo(const DerivedUnitImpl& other) const
{
    return 1;   // Affine units come after derived units
}

int AffineUnitImpl::compareTo(const AffineUnitImpl& other) const
{
    int cmp = core.compare(other.core);
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

bool AffineUnitImpl::isConvertible(const UnitImpl& other) const
{
    return other.isConvertibleTo(*this);
}

bool AffineUnitImpl::isConvertibleTo(const BaseUnitImpl& other) const
{
    return core.isConvertibleTo(other);
}

bool AffineUnitImpl::isConvertibleTo(const DerivedUnitImpl& other) const
{
    return core.isConvertibleTo(other);
}

bool AffineUnitImpl::isConvertibleTo(const AffineUnitImpl& other) const
{
    return core.isConvertible(other.core);
}

double AffineUnitImpl::convert(const double value) const
{
    return slope*value + intercept;
}

UnitImpl* AffineUnitImpl::multiply(const UnitImpl& other) const
{
    if (intercept)
        throw std::logic_error("Multiplication by an offset unit isn't supported");
    return nullptr;
}

UnitImpl* AffineUnitImpl::multiplyBy(const BaseUnitImpl& other) const
{
    if (intercept != 0)
        throw std::logic_error("Multiplication by an offset unit isn't supported");

    auto* newCore = core.multiplyBy(other);
    return slope == 1
            ? newCore
            : new AffineUnitImpl(*newCore, slope, 0);
}

UnitImpl* AffineUnitImpl::multiplyBy(const DerivedUnitImpl& other) const
{
    if (intercept != 0)
        throw std::logic_error("Multiplication by an offset unit isn't supported");

    auto* newCore = core.multiplyBy(other);
    return slope == 1
            ? newCore
            : new AffineUnitImpl(*newCore, slope, 0);
}

UnitImpl* AffineUnitImpl::multiplyBy(const AffineUnitImpl& other) const
{
    if (intercept != 0 || other.intercept != 0)
        throw std::logic_error("Multiplication by an offset unit isn't supported");

    auto* newCore = core.multiply(other.core);
    const auto newSlope = slope*other.slope;
    return newSlope == 1
            ? newCore
            : new AffineUnitImpl(*newCore, newSlope, 0);
}

} // Namespace
