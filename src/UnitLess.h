/**
 * This file defines a function class for comparing two units.
 *
 *        File: UnitLess.h
 *  Created on: Aug 13, 2025
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

#include <functional>

namespace std {
    using namespace quantity;

    /// Function class for comparing units. Used by std::set and std::map.
    template<>
    struct less<Unit> {
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
} // Namespace std
