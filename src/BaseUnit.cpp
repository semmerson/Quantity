/**
 * This file implements a class for base units of physical quantities.
 *
 *        File: BaseUnit.h
 *  Created on: Aug 1, 2025
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

#include "BaseUnit.h"

#include <unordered_set>

using namespace std;

namespace quantity {

/// Implementation of base units of physical quantities.
class BaseUnit::Impl final
{
private:
    const Dimension     dimension;  ///< Associated dimension
    const std::string   name;       ///< Unit name
    const std::string   symbol;     ///< Unit symbol
    static unordered_set<Dimension> dimSet;     ///< Set of extant dimensions
    static unordered_set<string>    nameSet;    ///< Set of extant base unit names
    static unordered_set<string>    symSet;     ///< Set of extant base unit symbols

public:
    /**
     * Constructs.
     * @param[in] dimension Associated dimension
     * @param[in] name      Unit name
     * @param[in] symbol    Unit symbol
     */
    Impl(   const Dimension&    dimension,
            const std::string&  name,
            const std::string&  symbol)
        : dimension(dimension)
        , name(name)
        , symbol(symbol)
    {
        if (name.size() == 0)
            throw invalid_argument("Empty base unit name");
        if (symbol.size() == 0)
            throw invalid_argument("Empty base unit symbol");
        if (    dimSet.count(dimension) ||
                nameSet.count(name) ||
                symSet.count(symbol))
            throw invalid_argument("Duplicate base unit");

        dimSet.insert(dimension);
        nameSet.insert(name);
        symSet.insert(symbol);
    }
};

unordered_set<Dimension> BaseUnit::Impl::dimSet;     ///< Set of extant dimensions
unordered_set<string>    BaseUnit::Impl::nameSet;    ///< Set of extant base unit names
unordered_set<string>    BaseUnit::Impl::symSet;     ///< Set of extant base unit symbols

BaseUnit::BaseUnit(Impl* impl)
    : pImpl{impl}
{}

BaseUnit::BaseUnit(
            const Dimension&    dimension,
            const std::string&  name,
            const std::string&  symbol)
    : BaseUnit(new Impl(dimension, name, symbol))
{}

} // Namespace
