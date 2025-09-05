/**
 * This file declares a physical dimension (e.g., length, mass).
 *
 *        File: Dimension.h
 *  Created on: Jul 14, 2025
 *      Author: Steven R. Emmerson
 *
 *    Copyright 2025 Steven R. Emmerson, All rights reserved
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

#include <cstddef>
#include <memory>
#include <string>

using namespace std;

namespace quantity {

/**
 * A physical dimension (e.g., length, mass).
 */
class Dimension final {
private:
    /// The implementation
    class Impl;

	/// Smart pointer to an implementation
	shared_ptr<Impl> pImpl;

	/**
	 * Constructs
	 * @param[in] impl  An implementation
	 */
	Dimension(Impl* impl);

public:
	/// Default constructs.
	Dimension() =default;

	/**
	 * Constructs
	 * @param[in] name                  The name for the dimension (e.g., "Mass")
	 * @param[in] symbol                The associated symbol (e.g., "M")
	 * @throw     std::invalid_argument The name is empty or the name is already in use
	 */
	Dimension(  const string&   name,
	            const string&   symbol);

	/**
	 * Copy constructs.
	 * @param[in] dim   A physical dimension
	 */
	Dimension(const Dimension& dim) =default;

	/**
	 * Returns the hash code of this instance.
	 * @return                  The hash code of this instance
	 * @throw std:: logic_error This instance has not been initialized
	 */
	size_t hash() const;

	/**
	 * Compares this instance with another.
	 * @param[in] other         The other instance
	 * @return                  A value less than, equal to, or greater than zero as this instance
	 *                          is considered less than, equal to, or greater than the other,
	 *                          respectively.
	 * @throw std:: logic_error This instance has not been initialized
	 */
	int compare(const Dimension& other) const;

	/**
	 * Returns a string representation.
	 * @throw std:: logic_error This instance has not been initialized
	 */
	string to_string() const;

	/**
	 * Clears the dimension database.
	 */
	static void clear();
};

} // namespace quantity
