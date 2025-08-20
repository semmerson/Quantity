/**
 * This file supports the dimensionality of a physical quantity. For example, the dimensionality of
 * power is mass times length squared divided by time cubed (i.e., M·L^2·T^-3).
 *
 *        File: Dimensionality.h
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

#include "Dimension.h"
#include "DimensionalityImpl.h"

#include <memory>

namespace quantity {

using namespace std;

/// The dimensionality of a physical quantity.
class Dimensionality
{
public:
    /// Type of PIMPL smart pointer
    using Pimpl = shared_ptr<DimensionalityImpl>;

    /// Smart pointer to the implementation for automatic deletion
    Pimpl pImpl;

    /**
     * Constructs from a pointer to an implementation.
     * @param[in] impl  Pointer to an implementation.
     */
    Dimensionality(DimensionalityImpl* impl);

    /// Default constructs.
    Dimensionality();

    /**
     * Constructs from a dimension and a rational exponent.
     * @param[in] dim   The associated dimension
     * @param[in] numer The numberator of the exponent
     * @param[in] denom The denominator of the exponent
     */
    Dimensionality(const Dimension dim,
                   const int       numer = 1,
                   const int       denom = 1);

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
    Dimensionality multiply(const Dimensionality& other) const;
};

} // namespace quantity
