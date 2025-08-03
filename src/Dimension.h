/**
 * This file declares a class for a physical dimension.
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

#include <memory>
#include <string>

using namespace std;

namespace quantity {

/**
 * Handle class for a physical dimension (e.g., length, mass).
 */
class Dimension {
private:
    /// The implementation
    class Impl;

	/// Smart pointer to an implementation
	shared_ptr<Impl> pImpl;

public:
	/**
	 * Constructs
	 * @param[in] impl  An implementation
	 * @throw           std::invalid_argument if the name is empty or the name is
	 *                  already in use
	 */
	Dimension(Impl* impl);

	/**
	 * Constructs
	 * @param name  Name of the dimension (e.g., "length")
	 * @throw       std::invalid_argument if the name is empty or the name is
	 *              already in use
	 */
	Dimension(const string&  name);

	/**
	 * Constructs
	 * @param name  Name of the dimension (e.g., "length")
	 * @throw       std::invalid_argument if the name is empty or the name is
	 *              already in use
	 */
	Dimension(string&&  name);

	/**
	 * Returns the hash code of this instance.
	 * @return  The hash code of this instance
	 */
	size_t hash() const;

	/**
	 * Compares this instance with another.
	 * @param[in] other The other instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compare(const Dimension& other) const;
};

} // namespace quantity

#include <functional>

namespace std {
    using namespace quantity;

    /// Function class for hashing a dimension.
    template<>
    struct hash<Dimension> {
        /**
         * Returns the hash code of a dimension.
         * @param[in] dim   The dimension
         * @return          The hash code of the dimension
         */
        size_t operator()(const Dimension& dim) const {
            return dim.hash();
        }
    };

    /// Function class for comparing dimensions.
    template<>
    struct less<Dimension> {
        /**
         * Indicates if one instance is less than another
         * @param[in] lhs       The left-hand-side dimension
         * @param[in] rhs       The right-hand-side dimension
         * @retval    true      @a lhs is less than @a rhs
         * @retval    false     @a lhs is not less than @a rhs
         */
        bool operator()(const Dimension& lhs, const Dimension& rhs) const {
            return lhs.compare(rhs) < 0;
        }
    };

    /// Function class for comparing dimensions for equality.
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
