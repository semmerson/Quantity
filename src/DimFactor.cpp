/**
 * This file defines a single dimensional factor (e.g., "s^2").
 *
 *        File: DimFactor.cpp
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

#include "DimFactor.h"

#include <stdexcept>

using namespace std;

namespace quantity {

/// Implementation of a dimensional factor (e.g., "length^2")
class DimFactorImpl final
{
private:
    const Dimension dim;    ///< Associated dimension (e.g., length)
    int             numer;  ///< Exponent numerator
    int             denom;  ///< Exponent denominator. Always positive.

    /**
     * Returns the greatest common divisor of two integers.
     * @param[in] n1    One integer
     * @param[in] n2    Another integer
     * @return          The greatest common divisor. Always positive.
     */
    static int gcd(int n1, int n2)
    {
        auto a = abs(n1);
        auto b = abs(n2);
        if (b > a) {
            auto c = a;
            a = b;
            b = c;
        }

        int gcd;

        if (b == 0) {
            gcd = a;
        }
        else {
            do {
                gcd = b;
                auto rem = a - (a/b)*b;
                a = b;
                b = rem;
            } while (b != 0);
        }

        return gcd;
    }

public:
    /// Default constructs.
    DimFactorImpl()
        : dim{}
        , numer(0)
        , denom(0)
    {}

    /**
     * Constructs from a dimension and a rational exponent.
     * @param[in] dim   The dimension (e.g., length)
     * @param[in] n     The numerator of the exponent
     * @param[in] d     The denominator of the exponent
     */
    DimFactorImpl(const Dimension& dim,
                  const int        n,
                  const int        d)
        : dim{dim}
        , numer(n)
        , denom(d)
    {
        if (denom == 0)
            throw std::invalid_argument("Exponent denominator is zero");

        if (denom < 0) {
            denom = -denom;
            numer = -numer;
        }

        const auto div = gcd(numer, denom);
        numer /= div;
        denom /= div;
    }

    /**
     * Returns the numerator of the exponent.
     * @return The numerator of the exponent
     */
    int getNumer() const
    {
        return numer;
    }

    /**
     * Returns the denominator of the exponent.
     * @return The denominator of the exponent
     */
    int getDenom() const
    {
        return denom;
    }

    /**
     * Returns a string representation.
     * @return A string representation
     */
    string to_string() const
    {
        string rep = "";
        if (denom != 0) {
            rep = dim.to_string();
            if (denom != 1 || numer != 1) {
                rep += "^";
                if (denom > 1)
                    rep += "(";
                rep += std::to_string(numer);
                if (denom > 1)
                    rep += "/" + std::to_string(denom) + ")";
            }
        }
        return rep;
    }
    /**
     * Compares this instance with another.
     * @param[in] other The other instance
     * @return          A value less than, equal to, or greater than zero as this instance is
     *                  considered less than, equal to, or greater than the other instance
     */
    int compare(const DimFactorImpl& other) const
    {
        return dim.compare(other.dim);
    }

    /**
     * Raises a dimensional factor to a rational exponent.
     * @param[in] n             The numerator of the exponent
     * @param[in] d             The denominator of the exponent
     * @return                  The result of raising this instance to the given power
     * @throw std::domain_error The denominator of the exponent is zero
     */
    DimFactorImpl* pow(int n,
                       int d) const
    {
        if (d == 0)
            throw domain_error("Denominator of exponent is zero");

        auto newNumer = numer*n;
        auto newDenom = denom*d;
        return new DimFactorImpl(dim, newNumer, newDenom);
    }

    /**
     * Multiplies by another instance
     * @param[in] other         Another instance
     * @return                  The product of this instance and the other instance
     * @throw std::domain_error The dimensions don't match
     */
    DimFactorImpl* multiply(const DimFactorImpl& other) const
    {
        auto newNumer = numer*other.denom + other.numer*denom;
        auto newDenom = denom*other.denom;
        int  div = gcd(newNumer, newDenom);
        return new DimFactorImpl(dim, newNumer/div, newDenom/div);
    }
};

DimFactor::DimFactor(DimFactorImpl* impl)
    : pImpl{impl}
{}

DimFactor::DimFactor(
        const Dimension& dim,
        const int        numer,
        const int        denom)
    : DimFactor(new DimFactorImpl(dim, numer, denom))
{}

int DimFactor::getNumer() const
{
    return pImpl->getNumer();
}

int DimFactor::getDenom() const
{
    return pImpl->getDenom();
}

string DimFactor::to_string() const
{
    return pImpl->to_string();
}

int DimFactor::compare(const DimFactor& other) const
{
    return pImpl->compare(*other.pImpl);
}

DimFactor DimFactor::pow(const int numer,
                         const int denom) const
{
    return DimFactor(pImpl->pow(numer, denom));
}

DimFactor DimFactor::multiply(const DimFactor& other) const
{
    return DimFactor(pImpl->multiply(*other.pImpl));
}

} // namespace quantity
