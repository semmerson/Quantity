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
#include <string>

using namespace std;

namespace quantity {

class BaseUnit;
class DerivedUnit;
class AffineUnit;

/// Declaration of a unit of a physical quantity.
class Unit
{
protected:
    /// Default constructs.
    Unit() =default;

public:
    /// Types of units
    enum class Type
    {
        base,
        derived,
        affine,
    };

    /// Smart pointer to an implementation of a unit.
    using Pimpl = shared_ptr<const Unit>;

    /// Destroys.
    virtual ~Unit() noexcept =0;

    /**
     * Returns a base unit. Creates it if necessary.
     * @param[in] name      The name of the unit
     * @param[in] symbol    The symbol of the unit
     * @return              Smart pointer to the corresponding base unit
     */
    static Pimpl getBase(const string& name,
                         const string& symbol);

    /**
     * Returns a possibly affine unit. An affine unit has the form "y = ax + b", where "x" is a
     * numeric value in the underlying unit and "a" and "b" are the slope and intercept,
     * respectively. If the slope is 1 and the intercept is 0, then the underlying unit is returned.
     * @param[in] core                  The underlying unit
     * @param[in] slope                 The slope for converting values from the @ core unit
     * @param[in] intercept             The intercept for converting values from the @ core unit
     * @throw     std::invalid_argument The slope is zero
     */
    static Pimpl getAffine(const Pimpl& core,
                           const double slope,
                           const double intercept);

    /**
     * Returns a string representation.
     * @retval A string representation
     */
    virtual std::string to_string() const =0;

    /**
     * Indicates the type of this unit.
     * @return The type of this unit
     */
    virtual Type type() const =0;

    /**
     * Indicates if this instance is a base unit (e.g., meter).
     * @retval true  This instance is a base unit
     * @retval false This instance is not a base unit
     */
    virtual bool isBase() const =0;

    /**
     * Indicates if this unit is dimensionless.
     * retval true      This unit is dimensionless
     * retval false     This unit is not dimensionless
     */
    virtual bool isDimensionless() const =0;

    /**
     * Indicates if the origin of this unit is *not* zero
     * retval true      The origin of this unit is *not* zero
     * retval false     The origin of this unit is zero
     */
    virtual bool isOffset() const =0;

	/**
	 * Returns the hash code of this instance.
	 * @return The hash code of this instance
	 */
    virtual size_t hash() const =0;

	/**
	 * Compares this instance with another.
	 * @param[in] other The other instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
    virtual int compare(const Pimpl& other) const =0;

	/**
	 * Compares this instance with a base unit.
	 * @param[in] other The base unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
    virtual int compareTo(const BaseUnit& other) const =0;

	/**
	 * Compares this instance with a derived unit.
	 * @param[in] other The derived unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
    virtual int compareTo(const DerivedUnit& other) const =0;

	/**
	 * Compares this instance with an affine unit.
	 * @param[in] other The affine unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
    virtual int compareTo(const AffineUnit& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with another unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertible(const Pimpl& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with a base unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertibleTo(const BaseUnit& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with a derived unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertibleTo(const DerivedUnit& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with an affine unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertibleTo(const AffineUnit& other) const =0;

    /**
     * Converts a numeric value from any underlying unit to this unit.
     * @param[in] value  The value to be converted from the underlying unit
     * @return           The converted value
     */
    virtual double convertTo(const double value) const = 0;

    /**
     * Multiplies by another unit.
     * @param[in] unit   The other unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual Pimpl multiply(const Pimpl& unit) const =0;

    /**
     * Multiplies by a base unit.
     * @param[in] other  The base unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual Pimpl multiplyBy(const BaseUnit& other) const =0;

    /**
     * Multiplies by a derived unit.
     * @param[in] other  The derived unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual Pimpl multiplyBy(const DerivedUnit& other) const =0;

    /**
     * Multiplies by an affine unit.
     * @param[in] other  The affine unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual Pimpl multiplyBy(const AffineUnit& other) const =0;
};

} // namespace quantity
