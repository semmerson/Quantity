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

using namespace std;

namespace quantity {

class AffineUnitImpl;

/// Implementation of base units of physical quantities.
/**
 * Constructs.
 * @param[in] dim       Associated dimension
 * @param[in] name      Unit name
 * @param[in] symbol    Unit symbol
 */
BaseUnitImpl::BaseUnitImpl(
        const Dimension&    dim,
        const std::string&  name,
        const std::string&  symbol)
    : dimension(dim)
    , name(name)
    , symbol(symbol)
{
    if (name.size() == 0)
        throw invalid_argument("Empty base unit name");
    if (symbol.size() == 0)
        throw invalid_argument("Empty base unit symbol");
    if (    dimSet.count(dim) ||
            nameSet.count(name) ||
            symSet.count(symbol))
        throw invalid_argument("Duplicate base unit");

    dimSet.insert(dim);
    nameSet.insert(name);
    symSet.insert(symbol);
}

/**
 * Destroys.
 */
BaseUnitImpl::~BaseUnitImpl() {
    dimSet.erase(dimension);
    nameSet.erase(name);
    symSet.erase(symbol);
}

/**
 * Indicates if this unit is dimensionless.
 * retval true      This unit is dimensionless
 * retval false     This unit is not dimensionless
 */
bool BaseUnitImpl::isDimensionless() const {
    return false;
}

/**
 * Indicates this unit's origin is *not* zero
 * retval true      This unit's origin is *not* zero
 * retval false     This unit's origin is zero
 */
bool BaseUnitImpl::isOffset() const {
    return false;
}

/**
 * Indicates if numeric values in this unit are convertible with another unit.
 * @param[in] other The other unit
 * @retval    true  They are convertible
 * @retval    false They are not convertible
 */
bool BaseUnitImpl::isConvertible(const UnitImpl& other) const {
    return other.isConvertible(*this);
}

/**
 * Indicates if numeric values in this unit are convertible with a base unit.
 * @param[in] other The other unit
 * @retval    true  They are convertible
 * @retval    false They are not convertible
 */
bool BaseUnitImpl::isConvertible(const BaseUnitImpl& other) const {
    return this == &other; // There can be only one!
}

/**
 * Indicates if numeric values in this unit are convertible with an affine unit.
 * @param[in] other The other unit
 * @retval    true  They are convertible
 * @retval    false They are not convertible
 */
bool BaseUnitImpl::isConvertible(const AffineUnitImpl& other) const {
    return other.isConvertible(*this);
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

/**
 * Converts a numeric value.
 * @param[in] value  The value to be converted
 * @return           The converted value
 */
double BaseUnitImpl::convert(const double value) const {
    return value;
}

unordered_set<Dimension> BaseUnitImpl::dimSet;     ///< Set of extant dimensions
unordered_set<string>    BaseUnitImpl::nameSet;    ///< Set of extant base unit names
unordered_set<string>    BaseUnitImpl::symSet;     ///< Set of extant base unit symbols

} // Namespace
