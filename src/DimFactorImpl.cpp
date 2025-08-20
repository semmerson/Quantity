/**
 * This file implements a single dimensional factor (e.g., "s^2").
 *
 *        File: DimFactorImpl.cpp
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

#include "DimFactorImpl.h"

#include <cmath>
#include <stdexcept>

using namespace std;

namespace quantity {

int DimFactorImpl::gcd(int n1, int n2)
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
        gcd = n1 ? n1 : n2;
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

DimFactorImpl::DimFactorImpl()
    : dim{}
    , numer(0)
    , denom(0)
{}

DimFactorImpl::DimFactorImpl(
        const Dimension& dim,
        const int        n,
        const int        d)
    : dim{dim}
    , numer{n}
    , denom{d}
{
    if (d == 0)
        throw domain_error("Denominator is zero");

    if (d < 0) {
        numer = -numer;
        denom = -denom;
    }

    const auto div = gcd(numer, denom);
    numer /= div;
    denom /= div;
}

/**
 * Returns the numerator of the exponent.
 * @return The numerator of the exponent
 */
int DimFactorImpl::getNumer() const
{
    return numer;
}

/**
 * Returns the denominator of the exponent.
 * @return The denominator of the exponent
 */
int DimFactorImpl::getDenom() const
{
    return denom;
}

string DimFactorImpl::to_string() const
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

int DimFactorImpl::compare(const DimFactorImpl& other) const
{
    return dim.compare(other.dim);
}

DimFactorImpl* DimFactorImpl::pow(const int n,
                                  const int d) const
{
    if (d == 0)
        throw domain_error("Denominator of exponent is zero");

    auto newNumer = numer*n;
    auto newDenom = denom*d;
    int  div = gcd(newNumer, newDenom);
    return new DimFactorImpl(dim, newNumer/div, newDenom/div);
}

} // namespace quantity
