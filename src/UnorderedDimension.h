/**
 * This file supports using dimensions in unordered sets and maps.
 *
 *        File: UnorderedDimension.h
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

#include "Dimension.h"

#include <unordered_map>
#include <unordered_set>

namespace quantity {

/// Dimension equality functor
struct DimensionEqual {
    template<class T, class U>
    typename std::enable_if<std::is_base_of<Dimension, T>::value &&
                            std::is_base_of<Dimension, U>::value, bool>::type
    /**
     * Indicates if two instances are equal.
     * @param[in] lhs   The first instance
     * @param[in] rhs   The second instance
     * @retval    true  The instances are equal
     * @retval    false The instances are not equal
     */
    operator()(T const& lhs, U const& rhs) const noexcept {
        return lhs.compare(rhs) == 0; // calls most-derived compare()
    }
};

/// Dimension hash functor
struct DimensionHash {
    /**
     * Returns the hash code.
     * @param[in] dim   The dimension
     * @return          The hash code of the dimension
     */
    size_t operator()(const Dimension& dim) const noexcept {
        return dim.hash(); // calls T::hash(), virtual or not
    }
};

using UnorderedDimensionSet = std::unordered_set<Dimension, DimensionHash, DimensionEqual>;

template<typename V>
using UnorderedDimensionMap = std::unordered_map<Dimension, V, DimensionHash, DimensionEqual>;

} // namespace quantity
