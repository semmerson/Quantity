/**
 * This file defines a function class for determining if two physical dimensions are equal.
 *
 *        File: DimensionEqual.h
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

#include "Dimension.h"

#include <functional>

namespace std {
    using namespace quantity;

    /**
     * Function class for comparing dimensions for equality. Used by @a std:unordered_set and
     * @a <std::unordered_map>.
     */
    template<>
    struct equal_to<Dimension> {
        /**
         * Indicates if this instance is considered equal to another
         * @param[in] lhs       The left-hand-side dimension
         * @param[in] rhs       The right-hand-side dimension
         * @retval    true      @a lhs is equal to @a rhs
         * @retval    false     @a lhs is not equal to @a rhs
         */
        bool operator()(const Dimension& lhs, const Dimension& rhs) const {
            return lhs.compare(rhs) == 0;
        }
    };
} // Namespace std
