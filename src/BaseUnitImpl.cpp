/**
 * This file implements a base unit of physical quantities.
 *
 *        File: BaseUnit.h
 *  Created on: Aug 1, 2025
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

#include "BaseUnitImpl.h"

#include "AffineUnitImpl.h"

#include <stdexcept>

using namespace std;

namespace quantity {

/**
 * Constructs.
 * @param[in] name      Unit name
 * @param[in] symbol    Unit symbol
 */
BaseUnitImpl::BaseUnitImpl(
        const std::string&  name,
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

/**
 * Destroys.
 */
BaseUnitImpl::~BaseUnitImpl()
{
    nameSet.erase(name);
    symSet.erase(symbol);
}

size_t BaseUnitImpl::hash() const
{
    static auto myHash = std::hash<string>();
    return myHash(name);
}

/**
 * Compares this instance with another unit implementation.
 * @param[in] other The other implementation
 * @return          A value less than, equal to, or greater than zero as this instance is
 *                  considered less than, equal to, or greater than the other, respectively.
 */
int BaseUnitImpl::compare(const UnitImpl& other) const
{
    return -other.compare(*this);
}

/**
 * Compares this instance with a base unit.
 * @param[in] other The base unit instance
 * @return          A value less than, equal to, or greater than zero as this instance is
 *                  considered less than, equal to, or greater than the other, respectively.
 */
int BaseUnitImpl::compare(const BaseUnitImpl& other) const
{
    return name.compare(other.name);
}

/**
 * Compares this instance with an affine unit.
 * @param[in] other The affine unit instance
 * @return          A value less than, equal to, or greater than zero as this instance is
 *                  considered less than, equal to, or greater than the other, respectively.
 */
int BaseUnitImpl::compare(const AffineUnitImpl& other) const
{
    return -1;  // Base units always come before affine units
}

/**
 * Returns a string representation
 * @retval A string representation
 */
std::string BaseUnitImpl::to_string() const
{
    return name;
}

/**
 * Indicates if this unit is dimensionless.
 * retval true      This unit is dimensionless
 * retval false     This unit is not dimensionless
 */
bool BaseUnitImpl::isDimensionless() const
{
    return false;
}

/**
 * Indicates this unit's origin is *not* zero
 * retval true      This unit's origin is *not* zero
 * retval false     This unit's origin is zero
 */
bool BaseUnitImpl::isOffset() const
{
    return false;
}

/**
 * Indicates if numeric values in this unit are convertible with another unit.
 * @param[in] other The other unit
 * @retval    true  They are convertible
 * @retval    false They are not convertible
 */
bool BaseUnitImpl::isConvertible(const UnitImpl& other) const
{
    return other.isConvertible(*this);
}

/**
 * Indicates if numeric values in this unit are convertible with a base unit.
 * @param[in] other The other unit
 * @retval    true  They are convertible
 * @retval    false They are not convertible
 */
bool BaseUnitImpl::isConvertible(const BaseUnitImpl& other) const
{
    return this == &other; // There can be only one!
}

/**
 * Indicates if numeric values in this unit are convertible with an affine unit.
 * @param[in] other The other unit
 * @retval    true  They are convertible
 * @retval    false They are not convertible
 */
bool BaseUnitImpl::isConvertible(const AffineUnitImpl& other) const
{
    return other.isConvertible(*this);
}

/**
 * Converts a numeric value.
 * @param[in] value  The value to be converted
 * @return           The converted value
 */
double BaseUnitImpl::convert(const double value) const {
    return value;
}

/**
 * Multiplies by another unit.
 * @param[in] unit   The other unit
 * @return           A unit whose scale-transform is equal to this unit's times the other unit's
 */
UnitImpl* BaseUnitImpl::multiply(const UnitImpl* unit) const
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
#endif

unordered_set<string>    BaseUnitImpl::nameSet;    ///< Set of extant base unit names
unordered_set<string>    BaseUnitImpl::symSet;     ///< Set of extant base unit symbols

} // Namespace
