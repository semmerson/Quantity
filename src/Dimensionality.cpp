/**
 * This file defines the dimensionality of a physical quantity. For example, the dimensionality of
 * power is mass times length squared divided by time cubed (i.e., M·L^2·T^-3).
 *
 *        File: Dimensionality.cpp
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

#include "Dimensionality.h"

#include "Exponent.h"

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

using namespace std;

namespace quantity {

/// Implementation of dimensionality for a physical quantity.
class Dimensionality::Impl final
{
private:
    /// Dimension information
    struct DimInfo {
        const string name;      ///< Name of the dimension
        const string symbol;    ///< Symbol for the dimension
        string to_string() const {
            return symbol;
        }
        size_t hash() const {
            static std::hash<string> myHash;
            return myHash(name) ^ myHash(symbol);
        }
    };

    /**
     * Compares information on two dimensions
     * @param[in] info1     Information on the first dimension
     * @param[in] info2     Information on the second dimension
     * @retval    true      The first dimension is less than the second
     * @retval    false     The first dimension in not less than the second
     */
    struct DimInfoLess {
        bool operator()(const DimInfo& info1, const DimInfo& info2) {
            return info1.name < info2.name;
        }
    };

    /// The type of the map from dimension information to exponent
    using Factors = map<const DimInfo, Exponent, DimInfoLess>;

    /// The dimensional factors
    Factors factors;

public:
    /// Default constructs.
    Impl() =default;

    /**
     * Constructs from a dimension and a rational exponent.
     * @param[in] name      The name of the dimension
     * @param[in] symbol    The symbol for the dimension
     * @param[in] exp       The exponent of the dimension. If the exponent is zero, then the
     *                      resulting dimensionality will be empty.
     */
    Impl(   const string   name,
            const string   symbol,
            const Exponent exp)
    {
        if (!exp.isZero())
            factors.insert({{name, symbol}, exp});
    }

    /**
     * Returns the number of dimensions.
     * @return  The number of dimensions
     */
	size_t size() const
	{
	    return factors.size();
	}

	/**
	 * Indicates if this instance is a base dimension. Such a dimensionality has a size of one with
	 * an exponent of one.
	 * @retval true     This instance is a base dimension
	 * @retval false    This instance is not a base dimension
	 */
	bool isBaseDim() const
	{
	    return factors.size() == 1 && factors.begin()->second.isOne();
	}

    /**
     * Returns a string representation.
     * @return A string representation
     */
    string to_string() const
    {
        string rep;
        bool   haveFactor = false;

        for (auto iter = factors.begin(); iter != factors.end(); ++iter) {
            if (haveFactor) {
                rep += "·";
            }
            else {
                haveFactor = true;
            }
            rep += iter->first.to_string();
            if (!iter->second.isOne())
                rep += "^" + iter->second.to_string();
        }

        return rep;
    }

    /**
     * Returns the hash code of this instance.
     * @return  The hash code of this instance
     */
    size_t hash() const
    {
        size_t code = 0;

        for (auto& factor : factors)
            code ^= factor.first.hash() ^ factor.second.hash();

        return code;
    }

	/**
	 * Compares this instance with another instance.
	 * @param[in] other The other instance
	 * @return          A value less than, equal to, or greater than zero as this instance is
	 *                  considered less than, equal to, or greater than the other, respectively.
	 */
	int compare(const Impl& other) const
	{
        auto       iter1 = factors.begin();
        const auto end1 = factors.end();
        auto       iter2 = other.factors.begin();
        const auto end2 = other.factors.end();

        while (iter1 != end1 && iter2 != end2) {
            auto cmp = iter1->first.name.compare(iter2->first.name);// Primary sort on name
            if (cmp)
                return cmp;
            cmp = iter1->second.compare(iter2->second);             // Secondary sort on exponents
            if (cmp)
                return cmp;
            ++iter1;
            ++iter2;
        }

        return (iter1 == end1 && iter2 == end2)                 // Tertiary sort on length
                ? 0
                : iter1 == end1
                  ? -1
                  : 1;
	}

    /**
     * Returns a new instance that's the product of this instance and another instance.
     * @param[in] other Another instance
     * @return          The product of this instance and the other instance
     */
    Impl* multiply(const Impl& other) const
    {
        const auto meLarger = size() >= other.size();
        auto newImpl = new Impl(meLarger ? *this : other);

        for (const auto& factor : (meLarger ? other.factors : factors)) {
            auto iter = newImpl->factors.find(factor.first);
            if (iter == newImpl->factors.end()) {
                newImpl->factors.insert(factor);
            }
            else {
                iter->second = iter->second.add(factor.second);
            }
        }

        return newImpl;
    }

    /**
     * Returns a new instance that's the result of raising this instance to a power.
     * @param[in] pow   The power
     * @return          The result of raising this instance to the given power
     */
    Impl* pow(const Exponent& pow) const
    {
        auto newImpl = new Impl(*this);

        for (auto& factor : newImpl->factors)
            factor.second = factor.second.multiply(pow);

        return newImpl;
    }
};

Dimensionality::Dimensionality(Impl* impl)
    : pImpl(impl)
{}

Dimensionality::Dimensionality()
    : pImpl(new Impl())
{}

Dimensionality::Dimensionality(const string&   name,
                               const string&   symbol,
                               const Exponent& exp)
    : pImpl(new Impl(name, symbol, exp))
{}

Dimensionality::Dimensionality(const Dimensionality& other)
    : pImpl(new Impl(*other.pImpl))
{}

Dimensionality Dimensionality::get(const string& name,
                                   const string& symbol)
{
    static unordered_map<string, Dimensionality> nameMap;  ///< Name to base dimension map
    static unordered_map<string, Dimensionality> symMap;   ///< Symbol to base dimension map

    if (name.size() == 0)
        throw std::invalid_argument("Dimension name is empty");
    if (symbol.size() == 0)
        throw std::invalid_argument("Dimension symbol is empty");

    const auto nameIter = nameMap.find(name);
    const auto symIter = symMap.find(symbol);

    if (nameIter == nameMap.end() && symIter == symMap.end()) {
        Dimensionality dim(name, symbol, Exponent(1, 1));
        nameMap.insert({name, dim});
        symMap.insert({symbol, dim});
        return dim;
    }

    if (nameIter == nameMap.end() || symIter == symMap.end() ||
            nameIter->second.compare(symIter->second))
        throw std::invalid_argument("Name \"" + name + "\" or symbol \"" + symbol +
                "\" is already associated with a different base dimension");

    return nameIter->second;
}

size_t Dimensionality::size() const
{
    return pImpl->size();
}

bool Dimensionality::isBaseDim() const
{
    return pImpl->isBaseDim();
}

string Dimensionality::to_string() const
{
    return pImpl->to_string();
}

size_t Dimensionality::hash() const
{
    return pImpl->hash();
}

int Dimensionality::compare(const Dimensionality& other) const
{
    return pImpl->compare(*other.pImpl);
}

Dimensionality Dimensionality::multiply(const Dimensionality& other) const
{
    return Dimensionality(pImpl->multiply(*other.pImpl));
}

Dimensionality Dimensionality::divideBy(const Dimensionality& other) const
{
    return multiply(other.pow(-1));
}

Dimensionality Dimensionality::pow(const Exponent& exp) const
{
    return Dimensionality(pImpl->pow(exp));
}

} // namespace quantity
