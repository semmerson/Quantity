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
#include <cstddef>
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
     * Constructs from a rational number.
     * @param[in] numer The numerator of the exponent
     * @param[in] denom The denominator of the exponent
     * @throw     std::invalid_argument The denominator is zero
     */
    Exponent(int numer = 1,
             int denom = 1);

    /**
     * Returns a string representation.
     * @return A string representation
     */
    string to_string() const;

    /**
     * Indicates if this instance is zero.
     * @retval true     This instance is zero
     * @retval false    This instance is not zero
     */
    bool isZero() const;

    /**
     * Indicates if this instance is one.
     * @retval true     This instance is one
     * @retval false    This instance is not one
     */
    bool isOne() const;

    /**
     * Returns the numerator of the exponent.
     * @return The numerator of the exponent
     */
    int getNumer() const;

    /**
     * Returns the denominator of the exponent.
     * @return The denominator of the exponent. Will always be positive.
     */
    int getDenom() const;

    /**
     * Returns the hash code of this instance.
     * @return The hash code of this instance
     */
    size_t hash() const;

    /**
     * Compares this instance with another.
     * @param[in] other The other instance
     * @return          A value less than, equal to, or greater than zero as this instance is
     *                  considered less than, equal to, or greater than the other
     */
    int compare(const Exponent& other) const;

    /**
     * Multiplies this instance by another instance. This implements raising a unit factor to a
     * power.
     * @param[in] other                 The other instance
     * @return                          This instance multiplied by the given exponent
     */
    Exponent& multiply(const Exponent& other);

    /**
     * Adds another instance to this instance. This implements multiplying together two unit factors
     * with the same base unit.
     * @param[in] other Another instance
     * @return          This instance after being added to
     */
    Exponent& add(const Exponent& other);
};

} // namespace quantity
