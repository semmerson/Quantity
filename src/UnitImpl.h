/**
 * This file declares the implementation of support for units of physical quantities.
 *
 *        File: UnitImpl.h
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
#include "OrderedUnit.h"

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_set>

using namespace std;

namespace quantity {

class BaseUnitImpl;
class DerivedUnitImpl;
class AffineUnitImpl;

/// Declaration of the abstract implementation of a unit of a physical quantity.
class UnitImpl
{
public:
    /// Default constructs.
    UnitImpl() =default;

    /// Destroys
    virtual ~UnitImpl();

    /**
     * Returns a string representation.
     * @retval A string representation
     */
    virtual std::string to_string() const =0;

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
	virtual int compare(const UnitImpl& other) const =0;

	/**
	 * Compares this instance with a base unit.
	 * @param[in] other The base unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	virtual int compareTo(const BaseUnitImpl& other) const =0;

	/**
	 * Compares this instance with a derived unit.
	 * @param[in] other The derived unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	virtual int compareTo(const DerivedUnitImpl& other) const =0;

	/**
	 * Compares this instance with an affine unit.
	 * @param[in] other The affine unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	virtual int compareTo(const AffineUnitImpl& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with another unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertible(const UnitImpl& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with a base unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertibleTo(const BaseUnitImpl& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with a derived unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertibleTo(const DerivedUnitImpl& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with an affine unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertibleTo(const AffineUnitImpl& other) const =0;

    /**
     * Converts a numeric value.
     * @param[in] value  The value to be converted
     * @return           The converted value
     */
    virtual double convert(const double value) const = 0;

    /**
     * Multiplies by another unit.
     * @param[in] unit   The other unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiply(const UnitImpl& unit) const =0;

    /**
     * Multiplies by a base unit.
     * @param[in] other  The base unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiplyBy(const BaseUnitImpl& other) const =0;

    /**
     * Multiplies by a derived unit.
     * @param[in] other  The derived unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiplyBy(const DerivedUnitImpl& other) const =0;

    /**
     * Multiplies by an affine unit.
     * @param[in] other  The affine unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiplyBy(const AffineUnitImpl& other) const =0;
};

/// Definition of the implementation of a base unit of a physical quantity.
class BaseUnitImpl final : public UnitImpl
{
private:
    const string    name;       ///< Base unit name
    const string    symbol;     ///< Base unit symbol

    static unordered_set<string>    nameSet;    ///< Set of extant base unit names
    static unordered_set<string>    symSet;     ///< Set of extant base unit symbols

public:
    /// Default constructs.
    BaseUnitImpl();

    /**
     * Constructs.
     * @param[in] name    Unit name
     * @param[in] symbol  Unit symbol
     */
    BaseUnitImpl(const std::string& name,
                 const std::string& symbol);

    /// Destroys.
    ~BaseUnitImpl() noexcept;

    /**
     * Returns a string representation
     * @retval A string representation
     */
    std::string to_string() const override;

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
    int compare(const UnitImpl& other) const override;

	/**
	 * Compares this instance with a base unit.
	 * @param[in] other The base unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const BaseUnitImpl& other) const override;

	/**
	 * Compares this instance with a derived unit.
	 * @param[in] other The derived unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const DerivedUnitImpl& other) const override;

	/**
	 * Compares this instance with an affine unit.
	 * @param[in] other The affine unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const AffineUnitImpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with another unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertible(const UnitImpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with a base unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const BaseUnitImpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with a derived unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const DerivedUnitImpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with an affine unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const AffineUnitImpl& other) const override;

    /**
     * Converts a numeric value.
     * @param[in] value  The value to be converted
     * @return           The converted value
     */
    double convert(const double value) const override;

    /**
     * Multiplies by another unit.
     * @param[in] other             The other unit
     * @return                      A unit whose scale-transform is equal to this unit's times the
     *                              other unit's
     * @throw     std::logic_error  If this operation isn't supported with these units
     */
    UnitImpl* multiply(const UnitImpl& other) const override;

    /**
     * Multiplies by a base unit.
     * @param[in] other  The base unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiplyBy(const BaseUnitImpl& other) const override;

    /**
     * Multiplies by a derived unit.
     * @param[in] other  The derived unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiplyBy(const DerivedUnitImpl& other) const override;

    /**
     * Multiplies by an affine unit.
     * @param[in] other  The affine unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiplyBy(const AffineUnitImpl& other) const override;
};

/// Definition of the implementation of a derived unit of a physical quantity. A derived unit
/// comprises a set of zero or more base units and their associated exponents. No exponent will be
/// zero. An empty set is equivalent to the dimensionless unit one.
class DerivedUnitImpl final : public UnitImpl
{
private:
    /// A single unit factor of a derived unit.
    struct UnitFactor
    {
        const BaseUnitImpl& baseUnit;
        mutable Exponent    exponent;
        UnitFactor(const BaseUnitImpl& baseUnit)
            : baseUnit{baseUnit}
            , exponent{1, 1}   // Unity exponent by default
        {}
        UnitFactor(const BaseUnitImpl& baseUnit,
                   const Exponent&     exponent)
            : baseUnit{baseUnit}
            , exponent(exponent)
        {}
        bool isOne() const
        {
            return exponent.getNumer() == 0;
        }
    };
    /// Comparison functor for unit factors
    struct UnitFactorLess {
        bool operator()(const UnitFactor& factor1, const UnitFactor& factor2) {
            return factor1.baseUnit.compare(factor2.baseUnit) < 0;
        }
    };
    /// Container for unit factors.
    using UnitFactors = set<UnitFactor, UnitFactorLess>;
    /// This instance's unit factors
    UnitFactors factors;

    /**
     * Constructs from a single base unit factor. If the exponent of the factor is zero, then it
     * will be ignored.
     * @param[in] factor A base unit factor
     */
    DerivedUnitImpl(const UnitFactor& factor);

    /**
     * Constructs from a set of base unit factors. Factors with an exponent of zero will be ignored.
     * @param[in] factors A set of base unit factors
     */
    DerivedUnitImpl(const UnitFactors& factors);

public:
    /// Default constructs an empty derived unit. This is equivalent to the dimensionless unit one.
    DerivedUnitImpl() =default;

    /**
     * Constructs from a base unit and an exponent. If the exponent is zero, then the derived unit
     * will be empty.
     * @param[in] base  The base unit
     * @param[in] exp   The exponent of the base unit
     */
    DerivedUnitImpl(const BaseUnitImpl& base, const Exponent& exp = Exponent());

    /**
     * Returns a string representation
     * @retval A string representation
     */
    std::string to_string() const override;

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
    int compare(const UnitImpl& other) const override;

	/**
	 * Compares this instance with a base unit.
	 * @param[in] other The base unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const BaseUnitImpl& other) const;

	/**
	 * Compares this instance with a derived unit.
	 * @param[in] other The derived unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const DerivedUnitImpl& other) const;

	/**
	 * Compares this instance with an affine unit.
	 * @param[in] other The affine unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const AffineUnitImpl& other) const;

    /**
     * Indicates if numeric values in this unit are convertible with another unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertible(const UnitImpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with a base unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const BaseUnitImpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with a derived unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const DerivedUnitImpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with an affine unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const AffineUnitImpl& other) const override;

    /**
     * Converts a numeric value.
     * @param[in] value  The value to be converted
     * @return           The converted value
     */
    double convert(const double value) const override;

    /**
     * Multiplies by another unit.
     * @param[in] other  The other unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    UnitImpl* multiply(const UnitImpl& other) const override;

    /**
     * Multiplies by a base unit.
     * @param[in] other  The base unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiplyBy(const BaseUnitImpl& other) const override;

    /**
     * Multiplies by a derived unit.
     * @param[in] other  The derived unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiplyBy(const DerivedUnitImpl& other) const override;

    /**
     * Multiplies by an affine unit.
     * @param[in] other  The affine unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiplyBy(const AffineUnitImpl& other) const override;
};

/// Definition of the implementation of an affine unit of a physical quantity.
class AffineUnitImpl final : public UnitImpl
{
    const UnitImpl& core;       ///< The underlying unit
    const double    slope;      ///< The slope for converting a numeric value to the @ core unit
    const double    intercept;  ///< The intercept for converting a numeric value to the @ core unit

public:
    /**
     * Constructs
     * @param[in] core      The underlying unit from which this unit is derived
     * @param[in] slope     The slope to convert values to the @ core unit
     * @param[in] intercept The intercept to convert values to the @ core unit
     */
    AffineUnitImpl(
            const UnitImpl&   core,
            const double      slope,
            const double      intercept);

    /**
     * Returns a string representation
     * @retval A string representation
     */
    std::string to_string() const override;

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
    int compare(const UnitImpl& other) const override;

	/**
	 * Compares this instance with a base unit.
	 * @param[in] other The base unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const BaseUnitImpl& other) const override;

	/**
	 * Compares this instance with a derived unit.
	 * @param[in] other The derived unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const DerivedUnitImpl& other) const override;

	/**
	 * Compares this instance with an affine unit.
	 * @param[in] other The affine unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compareTo(const AffineUnitImpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with another unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertible(const UnitImpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with a base unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const BaseUnitImpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with a derived unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const DerivedUnitImpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with an affine unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertibleTo(const AffineUnitImpl& other) const override;

    /**
     * Converts a numeric value.
     * @param[in] value  The value to be converted
     * @return           The converted value
     */
    double convert(const double value) const override;

    /**
     * Multiplies by another unit.
     * @param[in] other         The other unit
     * @return                  A unit whose scale-transform is equal to this unit's times the other unit's
     * @throw std::logic_error  This operation is not meaningful
     */
    UnitImpl* multiply(const UnitImpl& other) const override;

    /**
     * Multiplies by a base unit.
     * @param[in] other  The base unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiplyBy(const BaseUnitImpl& other) const override;

    /**
     * Multiplies by a derived unit.
     * @param[in] other  The derived unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiplyBy(const DerivedUnitImpl& other) const override;

    /**
     * Multiplies by an affine unit.
     * @param[in] other  The affine unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    virtual UnitImpl* multiplyBy(const AffineUnitImpl& other) const override;
};

} // namespace quantity
