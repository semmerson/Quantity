/**
 * This file implements class `Dimension`.
 *
 *        File: Dimension.cpp
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

#include "Dimension.h"

#include <functional>
#include <stdexcept>
#include <unordered_set>

using namespace std;

namespace quantity {

/**
 * Implementation of a physical dimension (e.g., length, mass).
 */
class Dimension::Impl final
{
private:
    /// Name of the dimension (e.g., "length")
	const string name;

	/// Set of names of created dimensions
	static std::unordered_set<string> names;

	/**
	 * Finishes handling the name.
	 * @throw       std::invalid_argument if the name is empty or the name is
	 *              already in use
	 */
	void finishName()
	{
	    if (name.length() == 0)
	        throw invalid_argument("Dimension name is empty");
	    if (!names.insert(name).second)
	        throw invalid_argument("Dimension name is already in use");
	}

public:
	/**
	 * Constructs from a name.
	 * @param name  The name for the dimension
	 * @throw       std::invalid_argument if the name is empty or the name is
	 *              already in use
	 */
	Impl(const string& name)
		: name(name)
	{
	    finishName();
	}

	/**
	 * Constructs from a name.
	 * @param name  The name for the dimension
	 * @throw       std::invalid_argument if the name is empty or the name is
	 *              already in use
	 */
	Impl(string&& name)
		: name(name)
	{
	    finishName();
	}

	/**
	 * Destroys.
	 */
	~Impl() noexcept {
	    names.erase(name);
	}

	/**
	 * Returns the hash code of this instance.
	 * @return  The hash code of this instance
	 */
    size_t hash() const {
        static std::hash<std::string> myHash;
        return myHash(name);
    }

	/**
	 * Compares this instance with another.
	 * @param[in] other The other instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compare(const Impl& other) const {
	    static std::less<string> myLess;
	    return
            myLess(name, other.name)
            ? -1
            : myLess(other.name, name)
              ? 1
              : 0;
	}
};

std::unordered_set<string> Dimension::Impl::names;

Dimension::Dimension(const string& name)
	: pImpl(new Impl(name))
{}

Dimension::Dimension(string&& name)
	: pImpl(new Impl(name))
{}

size_t Dimension::hash() const
{
    return pImpl->hash();
}

int Dimension::compare(const Dimension& other) const
{
    return pImpl->compare(*other.pImpl);
}

} // namespace quantity
