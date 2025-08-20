/**
 * This file declares an implementation of a set of dimensions for a physical quantity.
 *
 *        File: DimensionalityImpl.h
 *  Created on: Aug 8, 2025
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
#include "OrderedDimFactor.h"

namespace quantity {

/// Implementation of dimensionality for a physical quantity.
class DimensionalityImpl final
{
private:
    DimFactorSet factors;

public:
    /// Default constructs.
    DimensionalityImpl() =default;

    /**
     * Constructs from a dimension and a rational exponent.
     * @param[in] dim   The associated dimension
     * @param[in] numer The numberator of the exponent
     * @param[in] denom The denominator of the exponent
     */
    DimensionalityImpl(const Dimension dim, const int numer, const int denom);

    /**
     * Returns a string representation.
     * @return A string representation
     */
    string to_string() const;

    /**
     * Multiplies by another instance
     * @param[in] other Another instance
     * @return          The product of this instance and the other instance
     */
    DimensionalityImpl* multiply(const DimensionalityImpl& other) const;
};

} // namespace quantity
