/**
 * This file declares the implementation of units of physical quantities.
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

#include <memory>

namespace quantity {

class BaseUnitImpl;     // Forward declaration
class AffineUnitImpl;   // Forward declaration

/// Declaration of the implementation of a unit of a physical quantities.
class UnitImpl
{
public:
    UnitImpl() =default;

    /// Destroys
    virtual ~UnitImpl() =default;

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
    virtual bool isConvertible(const BaseUnitImpl& other) const =0;

    /**
     * Indicates if numeric values in this unit are convertible with an affine unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    virtual bool isConvertible(const AffineUnitImpl& other) const =0;

#if 0
    /**
     * Multiplies by a base unit.
     * @param[in] other  The base unit
     * @return           A unit whose scale-transform is equal to this unit's multiplied by
     *                   the base unit's
     */
    virtual UnitImpl* multiply(const BaseUnitImpl* other) const =0;

    /**
     * Multiplies by an affine unit.
     * @param[in] other  The affine unit
     * @return           A unit whose scale-transform is equal to this unit's multiplied by
     *                   the affine unit's
     */
    virtual UnitImpl* multiply(const AffineUnitImpl* other) const =0;

    /**
     * Divides into a base unit.
     * @param[in] unit   The base unit
     * @return           A unit whose scale-transform is equal to this unit's divided into
     *                   the base unit's
     */
    virtual UnitImpl* divideInto(const BaseUnitImpl* other) const =0;

    /**
     * Divides into an affine unit.
     * @param[in] unit   The affine unit
     * @return           A unit whose scale-transform is equal to this unit's divided into
     *                   the affine unit's
     */
    virtual UnitImpl* divideInto(const AffineUnitImpl* other) const =0;
#endif

#if 0
    /**
     * Multiplies by another unit.
     * @param[in] unit   The other unit
     * @return           A unit whose scale-transform is equal to this unit's times the
     *                   other unit's
     */
    virtual UnitImpl* multiply(const UnitImpl* unit) const =0;

    /**
     * Divides by a numeric factor.
     * @param[in] factor The numeric factor
     * @return           A unit whose scale-transform is equal to this unit's divided by a
     *                   factor
     */
    virtual UnitImpl* divideBy(const double factor) const =0;

    /**
     * Divides by another unit.
     * @param[in] unit   The other unit
     * @return           A unit whose scale-transform is equal to this unit's divided by
     *                   the other unit's
     */
    virtual UnitImpl* divideBy(const UnitImpl* unit) const =0;

    /**
     * Raises to a numeric power.
     * @param[in] power         The numeric power
     * @return                  A unit whose scale-transform is equal to this unit's raised
     *                          to a power
     * @throw std::domain_error This unit can't be raised to a power
     */
    virtual UnitImpl* pow(const int power) const =0;

    /**
     * Takes a root.
     * @param[in] root          The numeric root
     * @return                  A unit whose scale-transform is equal to a root of this
     *                          unit's
     * @throw std::domain_error This unit can't have a root taken
     */
    virtual UnitImpl* root(const int root) const =0;
#endif

    /**
     * Converts a numeric value.
     * @param[in] value  The value to be converted
     * @return           The converted value
     */
    virtual double convert(const double value) const = 0;
};

} // namespace quantity
