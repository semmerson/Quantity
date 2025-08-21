/**
 * This file defines an implementation of a single dimensional factor (e.g., "length^2").
 *
 *        File: DimFactor.h
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

#include <stdexcept>

namespace quantity {

/// Implementation of a dimensional factor (e.g., "length^2")
class DimFactorImpl final
{
private:
    const Dimension dim;    ///< Associated dimension (e.g., length)
    int             numer;  ///< Exponent numerator
    int             denom;  ///< Exponent denominator. Always positive.

    /**
     * Returns the greatest common divisor of two integers.
     * @param[in] a     One integer
     * @param[in] b     Another integer
     * @return          The greatest common divisor. Always positive.
     */
    static int gcd(int a, int b);

public:
    /// Default constructs.
    DimFactorImpl();

    /**
     * Constructs from a dimension and a rational exponent.
     * @param[in] dim   The dimension (e.g., length)
     * @param[in] numer The numerator of the exponent
     * @param[in] denom The denominator of the exponent
     */
    DimFactorImpl(const Dimension& dim,
                  int              numer = 1,
                  int              denom = 1);

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
     *                  considered less than, equal to, or greater than the other instance
     */
    int compare(const DimFactorImpl& other) const;

    /**
     * Raises a dimensional factor to a rational exponent.
     * @param[in] numer         The numerator of the exponent
     * @param[in] denom         The denominator of the exponent
     * @return                  The result of raising this instance to the given power
     * @throw std::domain_error The denominator of the exponent is zero
     */
    DimFactorImpl* pow(const int numer,
                       const int denom) const;

    /**
     * Multiplies by another instance
     * @param[in] other         Another instance
     * @return                  The product of this instance and the other instance
     * @throw std::domain_error The dimensions don't match
     */
    DimFactorImpl* multiply(const DimFactorImpl& other) const;
};

} // namespace quantity
