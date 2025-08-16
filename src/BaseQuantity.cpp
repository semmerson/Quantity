/**
 * This file implements a base physical quantity (e.g., length, mass).
 *
 *        File: BaseQuantity.h
 *  Created on: Aug 12, 2025
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

#include "BaseQuantity.h"

#include "Dimension.h"
#include "DimensionHash.h"
#include "DimensionEqual.h"
#include "UnitHash.h"
#include "UnitEqual.h"

#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>

using namespace std;

namespace quantity {

/// Implementation of a base physical quantity (e.g., length, mass).
class BaseQuantityImpl final : public BaseQuantity
{
private:
    const Dimension dim;    ///< Associated physical dimension
    const BaseUnit  unit;   ///< Associated base unit

    static unordered_map<Dimension, Pimpl>                      dimMap;  ///< Dimension-to-impl map
    static unordered_map<BaseUnit,  Pimpl, UnitHash, UnitEqual> unitMap; ///< Unit-to-impl map

public:
    /**
     * Constructs.
     * @param[in] dim   Associated dimension (e.g., length)
     * @param[in] unit  Associated base unit (e.g., meter)
     */
    BaseQuantityImpl(const Dimension& dim,
                     const BaseUnit&  unit)
        : dim(dim)
        , unit(unit)
    {}

    /**
     * Returns an instance. Creates the instance if it doesn't already exist.
     * @param[in] dim               Associated dimension (e.g., length)
     * @param[in] unit              Associated base unit (e.g., meter)
     * @return                      The base quantity
     * @throw std::invalid_argument The dimension or unit is already associated with a different
     *                              base quantity
     */
    static Pimpl get(const Dimension& dim,
                     const BaseUnit&  unit)
    {
        Pimpl pImpl;

        // Ensure that a redefinition isn't being attempted
        if (dimMap.count(dim)) {
            pImpl = dimMap[dim];
            auto baseUnit = pImpl->baseUnit();
            if (baseUnit.compare(unit))
                throw invalid_argument("Dimension \"" + dim.to_string() +
                        "\" is already associated with base unit \"" + baseUnit.to_string() + "\"");
        }
        if (unitMap.count(unit)) {
            pImpl = unitMap[unit];
            auto dimension = pImpl->dimension();
            if (dimension.compare(dim))
                throw invalid_argument("Base unit \"" + unit.to_string() +
                        "\" is already associated with dimension \"" + dimension.to_string() +
                        "\"");
        }

        // Create a base quantity if one doesn't already exist
        if (!pImpl) {
            pImpl = make_shared<BaseQuantityImpl>(dim, unit);
            dimMap[dim] = pImpl;
            unitMap[unit] = pImpl;
        }

        return pImpl;
    }

    /**
     * Returns the associated physical dimension.
     * @return The associated physical dimension
     */
    const Dimension& dimension() const noexcept override
    {
        return dim;
    }

    /**
     * Returns the associated base unit.
     * @return The associated base unit
     */
    const BaseUnit& baseUnit() const noexcept override
    {
        return unit;
    }
};

/// Dimension-to-impl map
unordered_map<Dimension, BaseQuantity::Pimpl>                      BaseQuantityImpl::dimMap(7);
/// Unit-to-impl map
unordered_map<BaseUnit,  BaseQuantity::Pimpl, UnitHash, UnitEqual> BaseQuantityImpl::unitMap(7);

BaseQuantity::Pimpl BaseQuantity::get(const Dimension& dim,
                                      const BaseUnit&  unit)
{
    return BaseQuantityImpl::get(dim, unit);
}

BaseQuantity::~BaseQuantity(void) noexcept
{}

} // Namespace
