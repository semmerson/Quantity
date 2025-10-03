/**
 * This file implements a base unit of a physical quantity.
 *
 *        File: BaseUnit.h
 *  Created on: Aug 29, 2025
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

#include "BaseInfo.h"
#include "Dimensionality.h"

#include "Unit.h"

#include <unordered_set>

using namespace std;

namespace quantity {

/// Implementation of a base unit. NB: Not an actual unit: just an information holder.
class BaseInfoImpl final
{
private:
    const Dimensionality dim;        ///< Associated physical dimension
    const string         name;       ///< Base unit name
    const string         symbol;     ///< Base unit symbol

    static unordered_set<string>    nameSet;    ///< Set of extant base unit names
    static unordered_set<string>    symSet;     ///< Set of extant base unit symbols

public:
    /// Default constructs.
    BaseInfoImpl() =delete;

    /**
     * Constructs.
     * @param[in] dim               Associated physical dimension
     * @param[in] name              Unit name
     * @param[in] symbol            Unit symbol
     * @throw std::invalid_argument The dimensionality is not a base dimension
     * @throw std::invalid_argument The name or symbol is already in use
     */
    BaseInfoImpl(const Dimensionality& dim,
                 const string&         name,
                 const string&         symbol)
        : dim(dim)
        , name(name)
        , symbol(symbol)
    {
        if (!dim.isBaseDim())
            throw std::invalid_argument("Dimensionality is not a base dimension");
        if (name.size() == 0)
            throw std::invalid_argument("No name for base unit");
        if (symbol.size() == 0)
            throw std::invalid_argument("No symbol for base unit");

        if (nameSet.count(name))
            throw std::invalid_argument("Base unit \"" + name + "\" already exists");
        if (symSet.count(symbol))
            throw std::invalid_argument("Base unit \"" + symbol + "\" already exists");

        nameSet.insert(name);
        symSet.insert(symbol);
    }

    /// Destroys.
    ~BaseInfoImpl() noexcept
    {
        nameSet.erase(name);
        symSet.erase(symbol);
    }

    /**
     * Returns a string representation
     * @retval A string representation
     */
    std::string to_string() const
    {
        return symbol;
    }

    /**
     * Returns the hash code of this instance.
     * @return The hash code of this instance
     */
    size_t hash() const
    {
        static auto myHash = std::hash<string>();
        return myHash(name);
    }

    /**
     * Compares this instance with another unit implementation.
     * @param[in] other The other implementation
     * @return          A value less than, equal to, or greater than zero as this instance is
     *                  considered less than, equal to, or greater than the other, respectively.
     */
    int compare(const BaseInfoImpl& other) const
    {
        return symbol.compare(other.symbol);  // Alphabetic sort consonant with to_string()
    }
};

unordered_set<string>    BaseInfoImpl::nameSet;    ///< Set of extant base unit names
unordered_set<string>    BaseInfoImpl::symSet;     ///< Set of extant base unit symbols

BaseInfo::BaseInfo(const Dimensionality& dim,
                   const string&         name,
                   const string&         symbol)
    : pImpl(new BaseInfoImpl(dim, name, symbol))
{}

std::string BaseInfo::to_string() const
{
    return pImpl->to_string();
}

size_t BaseInfo::hash() const
{
    return pImpl->hash();
}

int BaseInfo::compare(const BaseInfo& other) const
{
    return pImpl->compare(*other.pImpl);
}

BaseInfo::operator Unit::Pimpl()
{
    return Unit::get(*this);
}

} // Namespace
