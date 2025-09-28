/**
 * This file declares a derived unit (e.g., "kg·m·s-2").
 *
 *        File: DerivedUnit.h
 *  Created on: Aug 4, 2025
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
#include "BaseInfo.h"
#include "Converter.h"

#include <map>

using namespace std;

namespace quantity {

/**
 * A derived unit of a physical quantity. A derived unit comprises a set of zero or more base units
 * and their associated exponents. No exponent will be zero. An empty set is equivalent to the
 * dimensionless unit one; a set with one factor is equivalent to a base unit.
 */
class CanonicalUnit final : public Unit
{
private:
    /// Comparison functor for information on base units
    struct BaseInfoLess {
        bool operator()(const BaseInfo& base1, const BaseInfo& base2) const {
            return base1.compare(base2) < 0;
        }
    };

    /// Container for unit factors.
    using UnitFactors = map<const BaseInfo, Exponent, BaseInfoLess>;

    /// A unit factor
    using UnitFactor = pair<const BaseInfo, Exponent>;

    /// This instance's unit factors. No factor shall be the dimensionless unit one.
    UnitFactors factors;

    /**
     * Constructs from a set of base unit factors. Factors with an exponent of zero will be ignored.
     * @param[in] factors A set of base unit factors
     */
    CanonicalUnit(const UnitFactors& factors);

public:
    /**
     * Default constructs an empty derived unit. The resulting instance is equivalent to the
     * dimensionless unit one.
     */
    CanonicalUnit() =default;

    /**
     * Constructs from base unit information and an exponent. If the exponent is zero, then the
     * base unit information will be ignored and the derived unit will be empty and equivalent to
     * the dimensionless unit one.
     * @param[in] baseInfo  Base unit information
     * @param[in] exp       Exponent for the base unit
     */
    CanonicalUnit(const BaseInfo& baseInfo, Exponent exp);

    /**
     * Constructs from information on a base unit. The exponent of the single base unit will be one.
     * @param[in] baseInfo  Base unit information
     */
    CanonicalUnit(const BaseInfo& baseInfo);

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
     * Compares this instance with another unit.
     * @param[in] other The other unit
     * @return          A value less than, equal to, or greater than zero as this instance is
     *                  considered less than, equal to, or greater than the other, respectively.
     */
    int compare(const Pimpl& other) const override;

	/**
	 * Compares this instance with a derived unit.
	 * @param[in] other The derived unit
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const CanonicalUnit& other) const override;

	/**
	 * Compares this instance with an affine unit.
	 * @param[in] other The affine unit
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
     * Returns a converter of numeric values to an output unit.
     * @param[in] output                Output unit
     * @throw std::invalid_argument     Values aren't convertible between the two units
     */
    Converter getConverterTo(const Pimpl& output) const override;

    /**
     * Returns a converter of numeric values in a canonical unit to this unit.
     * @param[in] input                 Input unit
     * @throw std::invalid_argument     Values aren't convertible between the two units
     */
    Converter getConverterFrom(const CanonicalUnit& input) const override;

    /**
     * Returns a converter of numeric values in an affine unit to this unit.
     * @param[in] input                 Input unit
     * @throw std::invalid_argument     Values aren't convertible between the two units
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

    /**
     * Returns a new unit that is the product of this instance and another unit.
     * @param[in] other  The other unit
     * @return           The product of this instance and the other unit
     */
    Pimpl multiply(const Pimpl& other) const override;

    /**
     * Returns a new unit that is the product of this instance and a derived unit.
     * @param[in] other  The derived unit
     * @return           The product of this instance and the other unit
     */
    Pimpl multiplyBy(const CanonicalUnit& other) const override;

    /**
     * Returns a new unit that is the product of this instance and an affine unit.
     * @param[in] other  The affine unit
     * @return           The product of this instance and the other unit
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
