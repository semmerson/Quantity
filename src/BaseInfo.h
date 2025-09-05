/**
 * This file declares a base unit of a physical quantity.
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

#pragma once

#include "Unit.h"

#include <memory>
#include <string>

using namespace std;

namespace quantity {

class BaseInfoImpl;
class Dimension;

/**
 * Information on a base unit of a physical quantity. NB: This class *isn't* a unit and so it
 * *doesn't* inherit from Unit.
 */
class BaseInfo final
{
public:
    /// Type of smart pointer to the implementation
    using Pimpl = std::shared_ptr<BaseInfoImpl>;

    /// Smart pointer to the implementation
    Pimpl pImpl;

    /// Default constructs.
    BaseInfo() =delete;

    /**
     * Constructs from a name and a symbol.
     * @param[in] dim     Associated physical dimension
     * @param[in] name    Base unit name
     * @param[in] symbol  Base unit symbol
     */
    BaseInfo(const Dimension& dim,
             const string&    name,
             const string&    symbol);

    /**
     * Returns a string representation
     * @retval A string representation
     */
    std::string to_string() const;

    /**
     * Returns the hash code of this instance.
     * @return The hash code of this instance
     */
    size_t hash() const;

    /**
     * Compares this instance with another unit implementation.
     * @param[in] other The other implementation
     * @return          A value less than, equal to, or greater than zero as this instance is
     *                  considered less than, equal to, or greater than the other, respectively.
     */
    int compare(const BaseInfo& other) const;

    /**
     * Implicitly converts this instance to a unit smart pointer.
     */
    operator Unit::Pimpl();
};

} // namespace quantity
