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
    const Pimpl refLevel;  ///< Reference level

public:
    class ToConverter;      ///< Converter of numeric values in this affine unit to an output unit.
    class FromConverter;    ///< Converter of numeric values in an input unit to this affine unit.

    /**
     * Constructs from a reference level and a logarithmic base.
     * @param[in] refLevel      Reference level unit (the numeric value one in this unit is the
     *                          reference level). Must not be an offset unit.
     * @param[in] base          Logarithmic base: Unit::LogBase::TWO, Unit::LogBase::E, or
     *                          Unit::LogBase::TEN.
     * @throw std::logic_error  @ refLevel is an offset unit
     */
    RefLogUnit(const Pimpl& refLevel, const BaseEnum base = BaseEnum::TEN);

    /**
     * Returns a string representation of this unit.
     * @retval A string representation of this unit
     */
    std::string to_string() const override;

    /**
     * Indicates the type of this unit.
     * @return The type of this unit
     */
    Unit::Type type() const override;

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
	 * Compares this instance with a referenced logarithmic unit.
	 * @param[in] other The referenced logarithmic unit
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const RefLogUnit& other) const override;

	/**
	 * Compares this instance with an unreferenced logarithmic unit.
	 * @param[in] other The unreferenced logarithmic unit
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const UnrefLogUnit& other) const override;

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
     * Indicates if numeric values in this unit are convertible with a referenced logarithmic unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const RefLogUnit& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with an unreferenced logarithmic
     * unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const UnrefLogUnit& other) const override;

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
     * Returns a converter of numeric values in a referenced logarithmic unit to this unit.
     * @param[in] input                 Input unit
     * @throw std::invalid_argument     Values aren't convertible between the two units
     */
    Converter getConverterFrom(const RefLogUnit& input) const override;

    /**
     * Returns a converter of numeric values in an unreferenced logarithmic unit to this unit.
     * @param[in] input                 Input unit
     * @throw std::invalid_argument     Values aren't convertible between the two units
     */
    Converter getConverterFrom(const UnrefLogUnit& input) const override;
};

} // namespace quantity
