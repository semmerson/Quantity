/**
 * This file implements a physical dimension (e.g., Length, Mass).
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

#include "BaseUnit.h"

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
	const string                    name;     ///< Name of the dimension (e.g., "Length")
	const string                    symbol;   ///< Symbol of the dimension (e.g., "L")

	static unordered_set<string>    names;    ///< Set of names of created dimensions
	static unordered_set<string>    symbols;  ///< Set of symbols of created dimensions

public:
	/**
	 * Constructs from a name and a symbol.
	 * @param[in] name                  The name for the dimension (e.g., "Mass")
	 * @param[in] symbol                The associated symbol (e.g., "M")
	 * @throw     std::invalid_argument An ID is empty or an ID is already in use
	 */
	Impl(   const string& name,
	        const string& symbol)
		: name(name)
	    , symbol(symbol)
	{
	    if (name.length() == 0)
	        throw invalid_argument("Dimension name is empty");
	    if (symbol.length() == 0)
	        throw invalid_argument("Dimension symbol is empty");

	    if (!names.insert(name).second)
	        throw invalid_argument("Dimension name \"" + name + "\" is already in use");
	    if (!symbols.insert(symbol).second)
	        throw invalid_argument("Dimension symbol \"" + symbol + "\" is already in use");
	}

	/**
	 * Copy constructs.
	 * @param[in] impl  Implementation to copy
	 */
	Impl(const Impl& impl) =delete; // There can be only one!

	/**
	 * Copy assigns.
	 * @param[in] rhs   Implementation to copy
	 */
	Impl& operator=(const Impl& rhs) =delete; // There can be only one!

	/**
	 * Destroys.
	 */
	~Impl() noexcept {
	    names.erase(name);
	    symbols.erase(symbol);
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

    /**
     * Returns a string representation
     * @retval A string representation
     */
	string to_string() const {
	    return name;
	}

	/// Clears the database.
	static void clear() {
	    names.clear();
	    symbols.clear();
	}
};

std::unordered_set<string> Dimension::Impl::names;
std::unordered_set<string> Dimension::Impl::symbols;

Dimension::Dimension(Impl* impl)
    : pImpl(impl)
{}

Dimension::Dimension(const string& name,
                     const string& symbol)
	: Dimension(new Impl(name, symbol))
{}

void Dimension::clear()
{
    Impl::clear();
}

size_t Dimension::hash() const
{
    return pImpl->hash();
}

int Dimension::compare(const Dimension& other) const
{
    return pImpl->compare(*other.pImpl);
}

string Dimension::to_string() const
{
    return pImpl->to_string();
}

} // namespace quantity
