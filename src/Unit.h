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

#include "Converter.h"
#include "Exponent.h"

#include <cstddef>
#include <string>

using namespace std;

namespace quantity {

class AffineUnit;
class BaseInfo;
class CanonicalUnit;
class Dimensionality;
class RefLogUnit;
class UnrefLogUnit;

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
        ONE,        ///< Canonical unit with zero base units (i.e., the dimensionless unit one)
        BASE,       ///< Canonical unit with one base unit
        CANONICAL,  ///< Canonical unit with two or more base units
        AFFINE,     ///< Affine unit (transformation from canonical unit has form "y=ax+b")
        REF_LOG,    ///< Logarithmic unit with a reference level
        UNREF_LOG,  ///< Logarithmic unit without a reference level
    };

    /// Logarithmic base enumeration
    enum class BaseEnum {
        TWO,    ///< Binary logarithm
        E,      ///< Natural logarithm
        TEN     ///< Common logarithm
    };

    /// Smart pointer to an implementation of a unit.
    using Pimpl = shared_ptr<const Unit>;

    /// Destroys.
    virtual ~Unit() noexcept =0;

    /**
     * Returns a canonical unit comprising a single base unit.
     * @param[in] baseInfo  Base unit information
     * @return              Corresponding canonical unit
     */
    static Pimpl get(const BaseInfo& baseInfo);

    /**
     * Returns a possibly affine unit. An affine unit has the form "y = ax + b", where "x" is the
     * underlying unit. If the slope is one and the intercept is zero, then it's not an affine unit
     * and the underlying unit is returned instead.
     * @param[in] core      The underlying unit
     * @param[in] slope     The slope for converting values from the @ core unit. May be one, in
     *                      which case @ core will be returned if the intercept is zero.
     * @param[in] intercept The intercept for converting values from the @ core unit. May be zero,
     *                      in which case @ core will be returned if @ slope is one.
     * @return              A new affine unit or @ core if the slope is one and the intercept is
     *                      zero
     */
    static Pimpl get(const Pimpl& core,
                     const double slope,
                     const double intercept);

    /**
     * Constructs a referenced logarithmic unit from a reference level and a logarithmic base.
     * @param[in] base      Logarithmic base: Unit::LogBase::TWO, Unit::LogBase::E, or
     *                      Unit::LogBase::TEN.
     * @param[in] refLevel  Reference level unit (the numeric value one in this unit is the
     *                      reference level)
     */
    static Pimpl get(const Unit::BaseEnum base,
                     const Pimpl&        refLevel);

    /**
     * Constructs an unreferenced logarithmic unit from a logarithmic base and the dimensionality of
     * the relevant physical quantity.
     * @param[in] base      Logarithmic base: Unit::LogBase::TWO, Unit::LogBase::E, or
     *                      Unit::LogBase::TEN.
     * @param[in] dim       Dimensionality of the relevant physical quantity
     * @return              Corresponding unreferenced logarithmic unit
     */
    static Pimpl get(const Unit::BaseEnum  base,
                     const Dimensionality& dim);

    /**
     * Returns a string representation of the transformation from a numeric value in the @ core unit
     * to a numeric value in this unit.
     * @retval A string representation
     */
    virtual std::string to_string() const =0;

    /**
     * Indicates the type of this unit.
     * @return The type of this unit
     */
    virtual Unit::Type type() const =0;

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
	 * Compares this instance to another.
	 * @param[in] other The other instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
    virtual int compare(const Pimpl& other) const =0;

	/**
	 * Compares this instance to a derived unit.
	 * @param[in] other The derived unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
    virtual int compareTo(const CanonicalUnit& other) const =0;

	/**
	 * Compares this instance to an affine unit.
	 * @param[in] other The affine unit instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
    virtual int compareTo(const AffineUnit& other) const =0;

	/**
	 * Compares this instance to a referenced logarithmic unit.
	 * @param[in] other The referenced logarithmic unit
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
    virtual int compareTo(const RefLogUnit& other) const =0;

	/**
	 * Compares this instance to an unreferenced logarithmic unit.
	 * @param[in] other The unreferenced logarithmic unit
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
    virtual int compareTo(const UnrefLogUnit& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with another unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertible(const Pimpl& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with a derived unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertibleTo(const CanonicalUnit& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with an affine unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertibleTo(const AffineUnit& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with a reference logarithmic unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertibleTo(const RefLogUnit& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with an unreferenced logarithmic
     * unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertibleTo(const UnrefLogUnit& other) const =0;

    /**
     * Returns a converter of numeric values in this unit to an output unit.
     * @throw std::invalid_argument     Values aren't convertible between the two units
     */
    virtual Converter getConverterTo(const Pimpl& output) const =0;

    /**
     * Returns a converter of numeric values in a canonical unit to this unit.
     * @param[in] input                     Input unit
     * @throw     std::invalid_argument     Values aren't convertible between the two units
     */
    virtual Converter getConverterFrom(const CanonicalUnit& input) const =0;

    /**
     * Returns a converter of numeric values in an affine unit to this unit.
     * @param[in] input                     Input unit
     * @throw     std::invalid_argument     Values aren't convertible between the two units
     */
    virtual Converter getConverterFrom(const AffineUnit& input) const =0;

    /**
     * Returns a converter of numeric values in a referenced log unit to this unit.
     * @param[in] input                     Input unit
     * @throw     std::invalid_argument     Values aren't convertible between the two units
     */
    virtual Converter getConverterFrom(const RefLogUnit& input) const =0;

    /**
     * Returns a converter of numeric values in an unreferenced log unit to this unit.
     * @param[in] input                     Input unit
     * @throw     std::invalid_argument     Values aren't convertible between the two units
     */
    virtual Converter getConverterFrom(const UnrefLogUnit& input) const =0;

    /**
     * Multiplies by another unit.
     * @param[in] unit              The other unit
     * @return                      A unit whose scale-transform is equal to this unit's times the other unit's
     * @throw     std::logic_error  Multiplication isn't supported
     */
    virtual Pimpl multiply(const Pimpl& unit) const =0;

    /**
     * Multiplies by a derived unit.
     * @param[in] other             The derived unit
     * @return                      A unit whose scale-transform is equal to this unit's times the other unit's
     * @throw     std::logic_error  Multiplication isn't supported
     */
    virtual Pimpl multiplyBy(const CanonicalUnit& other) const =0;

    /**
     * Multiplies by an affine unit.
     * @param[in] other             The affine unit
     * @return                      A unit whose scale-transform is equal to this unit's times the other unit's
     * @throw     std::logic_error  Multiplication isn't supported
     */
    virtual Pimpl multiplyBy(const AffineUnit& other) const =0;

    /**
     * Returns the quotient of this instance divided by another instance.
     * @param[in] unit          The other instance
     * @return                  The quotient of this instance divided by the other instance
     * @throw std::logic_error  Division isn't supported for this instance
     */
    Pimpl divideBy(const Pimpl& unit) const; // NB: Not pure

    /**
     * Returns, in a new instance, this instance raised to a power.
     * @param[in] exp   The exponent
     * @return          The result
     */
    virtual Pimpl pow(const Exponent exp) const =0;
};

} // namespace quantity
