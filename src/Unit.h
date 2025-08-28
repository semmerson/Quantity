/**
 * This file declares support for units of physical quantities.
 *
 *        File: Unit.h
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

#pragma once

#include "Exponent.h"

#include <cstddef>
#include <memory>
#include <string>

using namespace std;

namespace quantity {

class UnitImpl;

/// Declaration of a unit of a physical quantity.
class Unit
{
public:
    /// Type of PIMPL smart pointer
    using Pimpl = std::shared_ptr<UnitImpl>;

    /// Smart pointer to the implementation for automatic deletion
    Pimpl pImpl;

    /**
     * Constructs.
     */
    Unit() =default;

    /**
     * Constructs from a pointer to an implementation.
     * @param[in] impl  Pointer to an implementation
     */
    Unit(UnitImpl* impl);

    /**
     * Copy assigns.
     * @param[in] rhs  The value to be assigned to this instance
     * @retval         This instance with the assigned value
     */
    Unit& operator=(const Unit& rhs);

    /**
     * Indicates if this instance is valid (i.e., wasn't default constructed).
     * @retval true     This instance is valid
     * @retval false    This instance is not valid
     */
    operator bool() const noexcept;

	/**
	 * Returns the hash code of this instance.
	 * @return  The hash code of this instance
	 */
	size_t hash() const;

    /**
     * Returns a string representation
     * @retval A string representation
     */
    std::string to_string() const;

    /**
     * Indicates if this unit is dimensionless.
     * retval true      This unit is dimensionless
     * retval false     This unit is not dimensionless
     */
    bool isDimensionless() const;

    /**
     * Indicates this unit's origin is *not* zero
     * retval true      This unit's origin is *not* zero
     * retval false     This unit's origin is zero
     */
    bool isOffset() const;

	/**
	 * Compares this instance with another.
	 * @param[in] other The other instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compare(const Unit& other) const;

    /**
     * Indicates if numeric values in this unit are convertible with another unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertible(const Unit& other) const;

    /**
     * Converts a numeric value.
     * @param[in] value  The value to be converted
     * @return           The converted value
     */
    double convert(const double value) const;

    /**
     * Multiplies by another unit.
     * @param[in] other             The other unit
     * @return                      A unit whose scale-transform is equal to this unit's times the
     *                              other unit's
     * @throw     std::logic_error  If this operation isn't supported with these units
     */
    Unit multiply(const Unit& other) const;
};

/// Declaration of a base unit of a physical quantity.
class BaseUnit : public Unit
{
public:
    /// Default constructs
    BaseUnit() =default;

    /**
     * Constructs.
     * @param[in] name    Unit name
     * @param[in] symbol  Unit symbol
     */
    BaseUnit(const string&  name,
             const string&  symbol);
};

/// Declaration of a derived unit of a physical quantity.
class DerivedUnit : public Unit
{
protected:
    friend class BaseUnit;

    /**
     * Constructs from a base unit and an exponent.
     * @param[in] base  The base unit
     * @param[in] exp   The exponent of the base unit
     */
    DerivedUnit(const BaseUnit& base,
                const Exponent& exp = Exponent{});
};

/// Declaration of an affine unit of a physical quantity.
class AffineUnit : public Unit
{
public:
    /**
     * Constructs.
     * @param[in] core                  The underlying unit
     * @param[in] slope                 The slope for converting values to the @ core unit
     * @param[in] intercept             The intercept for converting values to the @ core unit
     * @throw     std::invalid_argument The slope is zero
     */
    AffineUnit(
            const Unit&     core,
            const double    slope,
            const double    intercept);
};

} // namespace quantity
