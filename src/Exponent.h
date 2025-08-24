/**
 * This file declares a rational exponent for dimensions and units(e.g., "2/3").
 *
 *        File: Exponent.h
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

#include <memory>
#include <stdexcept>

using namespace std;

namespace quantity {

class ExponentImpl;

/// Implementation of an exponent.
class Exponent
{
private:
    /// Type of smart pointer to an implementation
    using Pimpl = shared_ptr<ExponentImpl>;

    /// Smart pointer to an implementation.
    Pimpl pImpl;

    /**
     * Constructs from a pointer to an implementation.
     * @param[in] impl  Pointer to an implementation
     */
    Exponent(ExponentImpl* impl);

public:
    /**
     * Constructs from a rational exponent.
     * @param[in] numer The numerator of the exponent
     * @param[in] denom The denominator of the exponent
     */
    Exponent(int numer = 1,
             int denom = 1);

    /**
     * Returns the numerator of the exponent.
     * @return The numerator of the exponent
     */
    int getNumer() const;

    /**
     * Returns the denominator of the exponent.
     * @return The denominator of the exponent
     */
    int getDenom() const;

    /**
     * Returns a string representation.
     * @return A string representation
     */
    string to_string() const;

    /**
     * Compares this instance with another.
     * @param[in] other The other instance
     * @return          A value less than, equal to, or greater than zero as this instance is
     *                  considered less than, equal to, or greater than the other
     */
    int compare(const Exponent& other) const;

    /**
     * Raises an instance to a rational exponent.
     * @param[in] numer         The numerator of the exponent
     * @param[in] denom         The denominator of the exponent
     * @return                  The result of raising this instance to the given power
     */
    Exponent pow(const int numer,
                 const int denom = 1) const;

    /**
     * Multiplies by another instance
     * @param[in] other         Another instance
     * @return                  The product of this instance and the other instance
     */
    Exponent multiply(const Exponent& other) const;
};

} // namespace quantity
