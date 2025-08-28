/**
 * This file defines a single unit factor (e.g., "s^2").
 *
 *        File: UnitFactor.cpp
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

#include "UnitFactor.h"

#include "Exponent.h"

#include <stdexcept>

using namespace std;

namespace quantity {

/// Implementation of a unit factor (e.g., "m^2")
class UnitFactorImpl final
{
private:
    const BaseUnit  base;    ///< Associated base unit (e.g., meter)
    const Exponent  exp;     ///< Exponent

    /// Default constructs.
    UnitFactorImpl()
        : base{}
        , exp{}
    {}

public:
    /**
     * Constructs from a dimension and an exponent.
     * @param[in] base  The base unit (e.g., meter)
     * @param[in] exp   The exponent
     */
    UnitFactorImpl(const BaseUnit& base,
                   const Exponent& exp)
        : base{base}
        , exp(exp)
    {}

    /**
     * Returns the numerator of the exponent.
     * @return The numerator of the exponent
     */
    int getNumer() const
    {
        return exp.getNumer();
    }

    /**
     * Returns the denominator of the exponent.
     * @return The denominator of the exponent
     */
    int getDenom() const
    {
        return exp.getDenom();
    }

    /**
     * Returns a string representation.
     * @return A string representation
     */
    string to_string() const
    {
        return "^" + exp.to_string();
    }
    /**
     * Compares this instance with another.
     * @param[in] other The other instance
     * @return          A value less than, equal to, or greater than zero as this instance is
     *                  considered less than, equal to, or greater than the other instance
     */
    int compare(const UnitFactorImpl& other) const
    {
        int cmp = base.compare(other.base);
        if (cmp == 0)
            cmp = exp.compare(other.exp);
        return cmp;
    }

    /**
     * Raises a dimensional factor to a rational exponent.
     * @param[in] n             The numerator of the exponent
     * @param[in] d             The denominator of the exponent
     * @return                  The result of raising this instance to the given power
     * @throw std::domain_error The denominator of the exponent is zero
     */
    UnitFactorImpl* pow(int n,
                       int d) const
    {
        if (d == 0)
            throw domain_error("Denominator of exponent is zero");

        auto newNumer = numer*n;
        auto newDenom = denom*d;
        return new UnitFactorImpl(dim, newNumer, newDenom);
    }

    /**
     * Multiplies by another instance
     * @param[in] other         Another instance
     * @return                  The product of this instance and the other instance
     * @throw std::domain_error The dimensions don't match
     */
    UnitFactorImpl* multiply(const UnitFactorImpl& other) const
    {
        auto newNumer = numer*other.denom + other.numer*denom;
        auto newDenom = denom*other.denom;
        int  div = gcd(newNumer, newDenom);
        return new UnitFactorImpl(dim, newNumer/div, newDenom/div);
    }
};

UnitFactor::UnitFactor(UnitFactorImpl* impl)
    : pImpl{impl}
{}

UnitFactor::UnitFactor(
        const Unit& dim,
        const int        numer,
        const int        denom)
    : UnitFactor(new UnitFactorImpl(dim, numer, denom))
{}

int UnitFactor::getNumer() const
{
    return pImpl->getNumer();
}

int UnitFactor::getDenom() const
{
    return pImpl->getDenom();
}

string UnitFactor::to_string() const
{
    return pImpl->to_string();
}

int UnitFactor::compare(const UnitFactor& other) const
{
    return pImpl->compare(*other.pImpl);
}

UnitFactor UnitFactor::pow(const int numer,
                         const int denom) const
{
    return UnitFactor(pImpl->pow(numer, denom));
}

UnitFactor UnitFactor::multiply(const UnitFactor& other) const
{
    return UnitFactor(pImpl->multiply(*other.pImpl));
}

} // namespace quantity
