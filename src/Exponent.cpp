/**
 * This file defines a rational exponent for dimensions and units.g., "s^2").
 *
 *        File: Exponent.cpp
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

#include "Exponent.h"

#include <cmath>
#include <functional>
#include <stdexcept>

using namespace std;

namespace quantity {

/// Implementation of a rational exponent.
class ExponentImpl final
{
private:
    int numer;  ///< Exponent numerator
    int denom;  ///< Exponent denominator. Always positive.

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

    /**
     * Returns the sign of an integer as -1, 0, or 1.
     * @param[in] i The integer
     * @return      -1, 0, or 1 for negative, zero, or positive, respectively
     */
    static inline int sign(const int i)
    {
        return (i > 0) - (i < 0);
    }

public:
    /// Default constructs.
    ExponentImpl()
        : numer(0)
        , denom(0)
    {}

    /**
     * Constructs a rational exponent.
     * @param[in] n     The numerator of the exponent
     * @param[in] d     The denominator of the exponent
     */
    ExponentImpl(const int n,
                 const int d)
        : numer(n)
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
     * Indicates if this instance is one.
     * @retval true     This instance is one
     * @retval false    This instance is not one
     */
    bool isUnity() const
    {
        return numer == 1 && denom == 1;
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

        if (denom != 1)
            rep += "(";
        rep += std::to_string(numer);
        if (denom != 1)
            rep += "/" + std::to_string(denom) + ")";

        return rep;
    }

    /**
     * Returns the hash code of this instance.
     * @return The hash code of this instance
     */
    size_t hash() const
    {
        static const auto myHash = std::hash<int>();
        return myHash(numer) ^ myHash(denom);
    }

    /**
     * Compares this instance with another.
     * @param[in] other The other instance
     * @return          A value less than, equal to, or greater than zero as this instance is
     *                  considered less than, equal to, or greater than the other instance
     */
    int compare(const ExponentImpl& other) const
    {
        const int s1 = sign(numer);
        const int s2 = sign(other.numer);

        if (s1 == s2 || (s1 >= 0 && s2 >= 0)) {
            const int n1 = abs(numer*other.denom);
            const int n2 = abs(other.numer*denom);
            return n1 < n2
                    ? -1
                    : n1 == n2
                      ? 0
                      : 1;
        }
        return (s1 < 0)
                ? 1
                : (s2 < 0)
                  ? -1
                  : 0;
    }

    /**
     * Multiplies this instance by a rational number.
     * @param[in] n             The numerator of the rational number
     * @param[in] d             The denominator of the rational number
     * @return                  The result of multiplying this instance by the given amount
     * @throw std::domain_error The denominator of the rational number is zero
     */
    ExponentImpl& multiply(int n,
                           int d)
    {
        if (d == 0)
            throw domain_error("Denominator is zero");

        numer *= n;
        denom *= d;
        if (denom < 0) {
            numer = -numer;
            denom = -denom;
        }
        int  div = gcd(numer, denom);
        numer /= div;
        denom /= div;
        return *this;
    }

    /**
     * Adds another instance
     * @param[in] other         Another instance
     * @return                  The sum of this instance and the other instance
     */
    ExponentImpl& add(const ExponentImpl& other)
    {
        auto newNumer = numer*other.denom + other.numer*denom;
        auto newDenom = denom*other.denom;
        int  div = gcd(newNumer, newDenom);
        numer = newNumer/div;
        denom = newDenom/div;
        return *this;
    }
};

Exponent::Exponent(ExponentImpl* impl)
    : pImpl{impl}
{}

Exponent::Exponent(const int numer,
                   const int denom)
    : Exponent(new ExponentImpl(numer, denom))
{}

bool Exponent::isUnity() const
{
    return pImpl->isUnity();
}

int Exponent::getNumer() const
{
    return pImpl->getNumer();
}

int Exponent::getDenom() const
{
    return pImpl->getDenom();
}

string Exponent::to_string() const
{
    return pImpl->to_string();
}

size_t Exponent::hash() const
{
    return pImpl->hash();
}

int Exponent::compare(const Exponent& other) const
{
    return pImpl->compare(*other.pImpl);
}

Exponent& Exponent::multiply(const int numer,
                             const int denom)
{
    pImpl->multiply(numer, denom);
    return *this;
}

Exponent& Exponent::add(const Exponent& other)
{
    pImpl->add(*other.pImpl);
    return *this;
}

} // namespace quantity
