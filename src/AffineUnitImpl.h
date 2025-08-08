/**
 * This file defines the implementation an affine unit of a physical quantity.  The scale-transform
 * of an affine unit has the form "y=ax+b".
 *
 *        File: AffineUnitImpl.h
 *  Created on: Aug 1, 2025
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

#include "UnitImpl.h"

namespace quantity {

/// Declaration of the implementation of an affine unit of a physical quantity.
class AffineUnitImpl : public UnitImpl
{
    const UnitImpl* core;      ///< The underlying unit
    const double    slope;     ///< The slope
    const double    intercept; ///< The intercept

public:
    AffineUnitImpl() =default;

    /**
     * Constructs
     * @param[in] core      The underlying unit
     * @param[in] slope     The slope
     * @param[in] intercept The intercept
     */
    AffineUnitImpl(
            const UnitImpl&   core,
            const double      slope,
            const double      intercept);

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
    bool isConvertible(const BaseUnitImpl& other) const override;

    /**
     * Indicates if numeric values in this unit are convertible with an affine unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertible(const AffineUnitImpl& other) const override;

    /**
     * Converts a numeric value.
     * @param[in] value  The value to be converted
     * @return           The converted value
     */
    double convert(const double value) const override;

    /**
     * Multiplies by another unit.
     * @param[in] unit   The other unit
     * @return           A unit whose scale-transform is equal to this unit's times the other unit's
     */
    UnitImpl* multiply(const UnitImpl* unit) const override;
};

} // Namespace
