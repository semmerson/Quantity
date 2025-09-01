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

#include "BaseUnit.h"

#include "AffineUnit.h"
#include "DerivedUnit.h"

namespace quantity {

unordered_set<string>    BaseUnit::nameSet;    ///< Set of extant base unit names
unordered_set<string>    BaseUnit::symSet;     ///< Set of extant base unit symbols

BaseUnit::BaseUnit(const std::string& name,
         const std::string& symbol)
    : name(name)
    , symbol(symbol)
{
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

BaseUnit::~BaseUnit()
{
    nameSet.erase(name);
    symSet.erase(symbol);
}

std::string BaseUnit::to_string() const
{
    return symbol;
}

/**
 * Indicates if this instance is a base unit (e.g., meter).
 * @retval true  This instance is a base unit
 * @retval false This instance is not a base unit
 */
bool BaseUnit::isBase() const
{
    return true;
}

bool BaseUnit::isDimensionless() const
{
    return false;
}

bool BaseUnit::isOffset() const
{
    return false;
}

size_t BaseUnit::hash() const
{
    static auto myHash = std::hash<string>();
    return myHash(name);
}

int BaseUnit::compare(const Pimpl& other) const
{
    return -other->compareTo(*this);
}

bool BaseUnit::isConvertible(const Pimpl& other) const
{
    return other->isConvertibleTo(*this);
}

double BaseUnit::convertDown(const double value) const
{
    return value;
}

BaseUnit::Pimpl BaseUnit::multiply(const Pimpl& other) const
{
    return other->multiplyBy(*this);
}

int BaseUnit::compareTo(const BaseUnit& other) const
{
    return symbol.compare(other.symbol);  // Alphabetic sort consonant with to_string()
}

int BaseUnit::compareTo(const DerivedUnit& other) const
{
    return -1;  // Base units always come before derived units
}

int BaseUnit::compareTo(const AffineUnit& other) const
{
    return -1;  // Base units always come before affine units
}

bool BaseUnit::isConvertibleTo(const BaseUnit& other) const
{
    return this == &other; // There can be only one!
}

bool BaseUnit::isConvertibleTo(const DerivedUnit& other) const
{
    return other.isConvertibleTo(*this); // Defer to the other unit
}

bool BaseUnit::isConvertibleTo(const AffineUnit& other) const
{
    return other.isConvertibleTo(*this); // Defer to the other unit
}

BaseUnit::Pimpl BaseUnit::multiplyBy(const BaseUnit& other) const
{
    return other.multiplyBy(DerivedUnit(*this));
}

BaseUnit::Pimpl BaseUnit::multiplyBy(const DerivedUnit& other) const
{
    return other.multiplyBy(*this);
}

BaseUnit::Pimpl BaseUnit::multiplyBy(const AffineUnit& other) const
{
    return other.multiplyBy(*this);
}

} // Namespace
