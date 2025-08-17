/**
 * This file supports using units in ordered sets and maps.
 *
 *        File: OrderedUnit.h
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

#include "Unit.h"

#include <map>
#include <set>

namespace quantity {

/// Unit less-than functor
struct UnitLess {
    /**
     * Indicates if one instance is less than another
     * @param[in] lhs       The left-hand-side unit
     * @param[in] rhs       The right-hand-side unit
     * @retval    true      @a lhs is less than @a rhs
     * @retval    false     @a lhs is not less than @a rhs
     */
    bool operator()(const Unit& lhs, const Unit& rhs) const {
        return lhs.compare(rhs) < 0;
    }
};

template<typename V>
using UnitSet = std::set<Unit, V, UnitLess>;

template<typename V>
using UnitMap = std::map<Unit, V, UnitLess>;

} // namespace quantity
