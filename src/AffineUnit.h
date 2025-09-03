/**
 * This file declares an affine unit of a physical quantity. An affine unit has the form
 * "y = ax + b", where "x" is a numeric value in the underlying unit and "y" is the equivalent value
 * in the affine unit.
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

#pragma once

#include "Unit.h"

namespace quantity {

/**
 * Definition of an affine unit of a physical quantity. An invariant is that (slope == 1 &&
 * intercept == 0) will always be false.
 */
class AffineUnit final : public Unit
{
    const Pimpl     core;        ///< The underlying unit
    const double    slope;       ///< The slope for converting a numeric value from the @ core unit.
                                 ///< May be one but only if the intercept isn't zero.
    const double    intercept;   ///< The intercept for converting a numeric value from the @ core
                                 ///< unit. May be zero but only if the slope isn't one.

public:
    /**
     * Constructs
     * @param[in] core                      The underlying unit from which this unit is derived
     * @param[in] slope                     The slope to convert values from the @ core unit
     * @param[in] intercept                 The intercept to convert values from the @ core unit
     * @throw     std::invalid_argument     Slope is zero
     * @throw     std::invalid_argument     Slope is one and intercept is zero
     */
    AffineUnit(
            const Pimpl&      core,
            const double      slope,
            const double      intercept);

    /**
     * Returns a string representation
     * @retval A string representation
     */
    std::string to_string() const override;

    /**
     * Indicates the type of this unit.
     * @return The type of this unit
     */
    Type type() const override;

    /**
     * Indicates if this unit is dimensionless.
     * retval true      This unit is dimensionless
     * retval false     This unit is not dimensionless
     */
    bool isDimensionless() const override;

    /**
     * Indicates if the origin of this unit is *not* zero
     * retval true      The origin of this unit is *not* zero
     * retval false     The origin of this unit is zero
     */
    bool isOffset() const override;

    /**
     * Returns the hash code of this instance.
     * @return The hash code of this instance
     */
    size_t hash() const override;

    /**
     * Compares this instance with another unit implementation.
     * @param[in] other The other implementation
     * @return          A value less than, equal to, or greater than zero as this instance is
     *                  considered less than, equal to, or greater than the other, respectively.
     */
    int compare(const Pimpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with another unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertible(const Pimpl& other) const override;

    /**
     * Converts a numeric value.
     * @param[in] value  The value to be converted
     * @return           The converted value
     */
    double convertTo(const double value) const override;

    /**
     * Multiplies by another unit.
     * @param[in] other         The other unit
     * @return                  A unit whose scale-transform is equal to this unit's times the other unit's
     * @throw std::logic_error  This operation is not meaningful
     */
    Pimpl multiply(const Pimpl& other) const override;

	/**
	 * Compares this instance with a derived unit.
	 * @param[in] other The derived unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const CanonicalUnit& other) const override;

	/**
	 * Compares this instance with an affine unit.
	 * @param[in] other The affine unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const AffineUnit& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with a derived unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const CanonicalUnit& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with an affine unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const AffineUnit& other) const override;

    /**
     * Multiplies by a derived unit.
     * @param[in] other  The derived unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    Pimpl multiplyBy(const CanonicalUnit& other) const override;

    /**
     * Multiplies by an affine unit.
     * @param[in] other  The affine unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    Pimpl multiplyBy(const AffineUnit& other) const override;

    /**
     * Returns this instance raised to a power in a new unit.
     * @param[in] exp   The exponent
     * @return          The result
     */
    Pimpl pow(const Exponent exp) const override;
};

} // namespace quantity
