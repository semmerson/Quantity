/**
 * This file defines an implementation of base units of physical quantities.
 *
 *        File: BaseUnitImpl.h
 *  Created on: Jul 31, 2025
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

#include "BaseUnit.h"

#include "Dimension.h"

#include <string>
#include <unordered_set>

namespace quantity {

using namespace std;

/// Definition of the implementation of base units of physical quantities.
class BaseUnitImpl final : public UnitImpl
{
private:
    const string    name;       ///< Base unit name
    const string    symbol;     ///< Base unit symbol

    static unordered_set<string>    nameSet;    ///< Set of extant base unit names
    static unordered_set<string>    symSet;     ///< Set of extant base unit symbols

public:
    BaseUnitImpl() =default;

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
