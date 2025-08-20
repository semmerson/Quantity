/**
 * This file supports using dimension factors in ordered sets and maps.
 *
 *        File: OrderedDimFactor.h
 *  Created on: Aug 17, 2025
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

#include "DimFactor.h"

#include <map>
#include <set>

namespace quantity {

/// DimFactor less-than functor
struct DimFactorLess {
    /**
     * Indicates if one instance is less than another
     * @param[in] lhs       The left-hand-side dimension
     * @param[in] rhs       The right-hand-side dimension
     * @retval    true      @a lhs is less than @a rhs
     * @retval    false     @a lhs is not less than @a rhs
     */
    bool operator()(const DimFactor& lhs, const DimFactor& rhs) const {
        return lhs.compare(rhs) < 0;
    }
};

/// An ordered set of dimensions.
using DimFactorSet = std::set<DimFactor, DimFactorLess>;

/// An ordered map with dimension as key.
template<typename V>
using DimFactorMap = std::map<DimFactor, V, DimFactorLess>;

} // namespace quantity
