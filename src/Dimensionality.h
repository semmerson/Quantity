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

#include <memory>

using namespace std;

namespace quantity {

class Exponent;

/// The dimensionality of a physical quantity.
class Dimensionality
{
protected:
    /// Implementation class
    class Impl;

    /// Type of smart pointer to an implementation
    using Pimpl = shared_ptr<Impl>;

    /// Smart pointer to the implementation for automatic deletion
    Pimpl pImpl;

    /**
     * Constructs from a pointer to an implementation.
     * @param impl  pointer to an implementation
     */
    Dimensionality(Impl* impl);

public:
    /// Default constructs.
    Dimensionality();

    /**
     * Constructs from a dimension and a rational exponent.
     * @param[in] dim               The associated dimension
     * @param[in] exp               The exponent. If it's zero, the the resulting dimensionality
     *                              will be empty.
     */
    Dimensionality(const string&   name,
                   const string&   symbol,
                   const Exponent& exp);

    /**
     * Returns the number of dimensions.
     * @return  The number of dimensions
     */
	size_t size() const;

    /**
     * Returns a string representation.
     * @return A string representation
     */
    string to_string() const;

	/**
	 * Returns the hash code of this instance.
	 * @return                  The hash code of this instance
	 * @throw std:: logic_error This instance has not been initialized
	 */
	size_t hash() const;

	/**
	 * Compares this instance with another instance.
	 * @param[in] other         The other instance
	 * @return                  A value less than, equal to, or greater than zero as this instance
	 *                          is considered less than, equal to, or greater than the other,
	 *                          respectively.
	 */
	int compare(const Dimensionality& other) const;

    /**
     * Multiplies by another instance
     * @param[in] other Another instance
     * @return          The product of this instance and the other instance
     */
    Dimensionality multiply(const Dimensionality& other) const;

    /**
     * Returns the quotient of this instance divided by another instance.
     * @param[in] other     The other instance
     * @return              The quotient of this instance divided by another instance
     */
    Dimensionality divideBy(const Dimensionality& other) const;

    /**
     * Returns the result of raising this instance to a power.
     * @param[in] exp   The power
     * @return          The result of raising this instance to the given power
     */
    Dimensionality pow(const Exponent& exp) const;
};

} // namespace quantity
