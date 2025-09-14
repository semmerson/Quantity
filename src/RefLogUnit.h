/**
 * This file declares a logarithmic unit with a reference level.
 *
 *        File: RefLogUnit.h
 *  Created on: Sep 14, 2025
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

#include "LogUnit.h"

namespace quantity {

/// A logarithmic unit with a reference level.
class RefLogUnit final : public LogUnit
{
private:
    const Pimpl ref;  ///< Reference level

public:
    /**
     * Constructs from a reference level and a logarithmic base.
     * @param[in] ref                       Reference level. Must not be an offset unit.
     * @param[in] base                      Logarithmic base
     * @throw     std::invalid_argument     The logarithmic base is not greater than one
     * @throw     std::invalid_argument     The reference level is an offset unit
     */
    RefLogUnit(const Pimpl& ref, const double base = 10);

    /**
     * Returns a string representation of this unit.
     * @retval A string representation of this unit
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
	 * Compares this instance with another.
	 * @param[in] other The other instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
    int compare(const Pimpl& other) const override;

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
     * Indicates if numeric values in this unit are convertible with another unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertible(const Pimpl& other) const override;

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
     * Returns a converter of numeric values in this unit to an output unit.
     * @throw std::invalid_argument     Values aren't convertible between the two units
     */
    Converter getConverterTo(const Pimpl& output) const override;

    /**
     * Returns a converter of numeric values in a Canonical unit to this unit.
     * @param[in] input                     Input unit
     * @throw     std::invalid_argument     Values aren't convertible between the two units
     */
    Converter getConverterFrom(const CanonicalUnit& input) const override;

    /**
     * Returns a converter of numeric values in an Affine unit to this unit.
     * @param[in] input                     Input unit
     * @throw     std::invalid_argument     Values aren't convertible between the two units
     */
    Converter getConverterFrom(const AffineUnit& input) const override;

    /**
     * Multiplies by another unit.
     * @param[in] unit   The other unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    Pimpl multiply(const Pimpl& unit) const override;

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
