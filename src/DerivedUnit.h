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

#include "BaseUnit.h"

#include <map>

using namespace std;

namespace quantity {

/// A derived unit of a physical quantity. A derived unit comprises a set of zero or more base units
/// and their associated exponents. No exponent will be zero. An empty set is equivalent to the
/// dimensionless unit one; a set with one factor is equivalent to a base unit.
class DerivedUnit final : public Unit
{
private:
    /// Comparison functor for base units
    struct BaseUnitLess {
        bool operator()(const BaseUnit& base1, const BaseUnit& base2) {
            // NB: Ignore the exponents
            return base1.compareTo(base2) < 0;
        }
    };

    /// Container for unit factors.
    using UnitFactors = map<BaseUnit, Exponent, BaseUnitLess>;

    /// A unit factor
    using UnitFactor = pair<const BaseUnit, Exponent>;

    /// This instance's unit factors. No factor shall be the dimensionless unit one.
    UnitFactors factors;

    /**
     * Constructs from a set of base unit factors. Factors with an exponent of zero will be ignored.
     * @param[in] factors A set of base unit factors
     */
    DerivedUnit(const UnitFactors& factors);

public:
    /**
     * Default constructs an empty derived unit. The resulting instance is equivalent to the
     * dimensionless unit one.
     */
    DerivedUnit() =default;

    /**
     * Constructs from a base unit and an exponent. If the exponent is zero, then the derived unit
     * will be empty and equivalent to the dimensionless unit one.
     * @param[in] base  The base unit
     * @param[in] exp   The exponent of the base unit
     */
    DerivedUnit(const BaseUnit& base, Exponent exp);

    /**
     * Constructs from a base unit. The exponent will be one.
     * @param[in] base  The base unit
     */
    DerivedUnit(const BaseUnit& base);

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
     * Indicates if this instance is a base unit (e.g., meter).
     * @retval true  This instance is a base unit
     * @retval false This instance is not a base unit
     */
    bool isBase() const override;

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
	 * Compares this instance with a base unit.
	 * @param[in] other The base unit
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const BaseUnit& other) const override;

	/**
	 * Compares this instance with a derived unit.
	 * @param[in] other The derived unit
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const DerivedUnit& other) const override;

	/**
	 * Compares this instance with an affine unit.
	 * @param[in] other The affine unit
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
     * Indicates if numeric values in this unit are convertible with a base unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const BaseUnit& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with a derived unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const DerivedUnit& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with an affine unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const AffineUnit& other) const override;

    /**
     * Converts a numeric value.
     * @param[in] value  The value to be converted
     * @return           The converted value
     */
    double convertTo(const double value) const override;

    /**
     * Returns a new unit that is the product of this instance and another unit.
     * @param[in] other  The other unit
     * @return           The product of this instance and the other unit
     */
    Pimpl multiply(const Pimpl& other) const override;

    /**
     * Returns a new unit that is the product of this instance and a base unit.
     * @param[in] other  The base unit
     * @return           The product of this instance and the other unit
     */
    Pimpl multiplyBy(const BaseUnit& other) const override;

    /**
     * Returns a new unit that is the product of this instance and a derived unit.
     * @param[in] other  The derived unit
     * @return           The product of this instance and the other unit
     */
    Pimpl multiplyBy(const DerivedUnit& other) const override;

    /**
     * Returns a new unit that is the product of this instance and an affine unit.
     * @param[in] other  The affine unit
     * @return           The product of this instance and the other unit
     */
    Pimpl multiplyBy(const AffineUnit& other) const override;
};


} // namespace quantity
