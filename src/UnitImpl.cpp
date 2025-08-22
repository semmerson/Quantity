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

using namespace std;

namespace quantity {

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
    return name;
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
    throw std::logic_error("Not implemented yet");
}

#if 0
/**
 * Multiplies by a base unit.
 * @param[in] other  The base unit
 * @return           A unit whose scale-transform is equal to this unit's multiplied by
 *                   the base unit's
 */
UnitImpl* BaseUnitImpl::multiply(const BaseUnitImpl* other) const {
    throw std::logic_error("Not implemented yet");
}

/**
 * Multiplies by an affine unit.
 * @param[in] other  The affine unit
 * @return           A unit whose scale-transform is equal to this unit's multiplied by
 *                   the affine unit's
 */
UnitImpl* BaseUnitImpl::multiply(const AffineUnitImpl* other) const {
    throw std::logic_error("Not implemented yet");
}
};
#endif

unordered_set<string>    BaseUnitImpl::nameSet(7);    ///< Set of extant base unit names
unordered_set<string>    BaseUnitImpl::symSet(7);     ///< Set of extant base unit symbols

AffineUnitImpl::AffineUnitImpl()
    : core(nullptr)
    , slope(0)
    , intercept(0)
{}

AffineUnitImpl::AffineUnitImpl(
        const UnitImpl&   core,
        const double      slope,
        const double      intercept)
    : core(&core)
    , slope(slope)
    , intercept(intercept)
{
    if (slope == 0)
        throw std::invalid_argument("The slope is zero");
}

std::string AffineUnitImpl::to_string() const
{
    return std::to_string(slope) + "(" + core->to_string() + ")" + std::to_string(intercept);
}

bool AffineUnitImpl::isDimensionless() const
{
    return core->isDimensionless();
}

bool AffineUnitImpl::isOffset() const
{
    return intercept != 0;
}

size_t AffineUnitImpl::hash() const
{
    static auto doubleHash = std::hash<double>();
    return core->hash() ^ doubleHash(slope) ^ doubleHash(intercept);
}

int AffineUnitImpl::compare(const UnitImpl& other) const
{
    return -other.compareTo(*this);
}

int AffineUnitImpl::compareTo(const BaseUnitImpl& other) const
{
    return -other.compareTo(*this);   // Defer to base unit
}

int AffineUnitImpl::compareTo(const AffineUnitImpl& other) const
{
    int cmp = core->compare(*other.core);
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
    return core->isConvertibleTo(other);
}

bool AffineUnitImpl::isConvertibleTo(const AffineUnitImpl& other) const
{
    return core->isConvertible(*other.core);
}

double AffineUnitImpl::convert(const double value) const
{
    return slope*value + intercept;
}

UnitImpl* AffineUnitImpl::multiply(const UnitImpl& other) const
{
    throw std::logic_error("Not implemented yet");
}

} // Namespace
