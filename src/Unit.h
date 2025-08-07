/**
 * This file declares a class for units of physical quantities.
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

#include "UnitImpl.h"

#include <memory>

namespace quantity {

/// Class for units of physical quantities.
class Unit
{
public:
    /// Type of PIMPL smart pointer
    using Pimpl = std::shared_ptr<UnitImpl>;

    /// Smart pointer to the implementation for automatic deletion
    Pimpl pImpl;

    /**
     * Constructs.
     */
    Unit() =default;

    /**
     * Constructs from a pointer to an implementation.
     * @param[in] impl  Pointer to an implementation
     */
    Unit(UnitImpl* impl);

    /**
     * Indicates if this unit is dimensionless.
     * retval true      This unit is dimensionless
     * retval false     This unit is not dimensionless
     */
    bool isDimensionless() const;

    /**
     * Indicates this unit's origin is *not* zero
     * retval true      This unit's origin is *not* zero
     * retval false     This unit's origin is zero
     */
    bool isOffset() const;

    /**
     * Indicates if numeric values in this unit are convertible with another unit.
     * @param[in] other The other unit
     * @retval    true  They are convertible
     * @retval    false They are not convertible
     */
    bool isConvertible(const Unit& other) const;

    /**
     * Multiplies by a numeric factor.
     * @param[in] factor The numeric factor
     * @return           A unit whose scale-transform is equal to this unit's times a
     *                   factor
     */
    Unit multiply(const double factor) const;

#if 0
    /**
     * Multiplies by another unit.
     * @param[in] other  The other unit
     * @return           A unit whose scale-transform is equal to this unit's times the
     *                   other unit's
     */
    Unit multiply(const Unit& other) const;

    /**
     * Divides by a numeric factor.
     * @param[in] factor The numeric factor
     * @return           A unit whose scale-transform is equal to this unit's divided by a
     *                   factor
     */
    Unit divideBy(const double factor) const;

    /**
     * Divides by another unit.
     * @param[in] other  The other unit
     * @return           A unit whose scale-transform is equal to this unit's divided by
     *                   the other unit's
     */
    Unit divideBy(const Unit& other) const;

    /**
     * Raises to a numeric power.
     * @param[in] power         The numeric power
     * @return                  A unit whose scale-transform is equal to this unit's raised
     *                          to a power
     * @throw std::domain_error This unit can't be raised to a power
     */
    Unit pow(const int power) const;

    /**
     * Takes a root.
     * @param[in] root          The numeric root
     * @return                  A unit whose scale-transform is equal to a root of this
     *                          unit's
     * @throw std::domain_error This unit can't have a root taken
     */
    Unit root(const int root) const;
#endif

    /**
     * Converts a numeric value.
     * @param[in] value  The value to be converted
     * @return           The converted value
     */
    double convert(const double value) const;
};

} // namespace quantity
