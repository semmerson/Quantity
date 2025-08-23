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
#include "DimFactor.h"
#include "OrderedDimFactor.h"

#include <memory>

using namespace std;

namespace quantity {

/// Implementation of dimensionality for a physical quantity.
class DimensionalityImpl final
{
private:
    DimFactorSet factors;

public:
    /// Default constructs.
    DimensionalityImpl() =default;

    /**
     * Constructs from a dimension and a rational exponent.
     * @param[in] dim   The associated dimension
     * @param[in] numer The numerator of the exponent
     * @param[in] denom The denominator of the exponent
     */
    DimensionalityImpl(const Dimension dim, const int numer, const int denom)
    {
        factors.insert(DimFactor(dim, numer, denom));
    }

    /**
     * Returns a string representation.
     * @return A string representation
     */
    string to_string() const
    {
        string rep{};
        bool   haveFactor = false;

        for (auto iter = factors.begin(); iter != factors.end(); ++iter) {
            if (haveFactor) {
                rep += "·";
            }
            else {
                haveFactor = true;
            }
            rep += iter->to_string();
        }

        return rep;
    }

    /**
     * Multiplies by another instance
     * @param[in] other Another instance
     * @return          The product of this instance and the other instance
     */
    DimensionalityImpl* multiply(const DimensionalityImpl& other) const
    {
        const DimFactorSet* smaller;
        const DimFactorSet* larger;
        if (factors.size() <= other.factors.size()) {
            smaller = &factors;
            larger = &other.factors;
        }
        else {
            larger = &factors;
            smaller = &other.factors;
        }

        auto newImpl = new DimensionalityImpl;
        newImpl->factors = *larger;

        for (const auto factor : *smaller) {
            auto iter = newImpl->factors.find(factor);
            if (iter == newImpl->factors.end()) {
                newImpl->factors.insert(factor);
            }
            else {
                newImpl->factors.erase(iter);
                newImpl->factors.insert(iter->multiply(factor));
            }
        }

        return newImpl;
    }
};

Dimensionality::Dimensionality(DimensionalityImpl* impl)
    : pImpl{impl}
{}

Dimensionality::Dimensionality()
    : Dimensionality(new DimensionalityImpl())
{}

Dimensionality::Dimensionality(const Dimension dim, const int numer, const int denom)
    : Dimensionality(new DimensionalityImpl(dim, numer, denom))
{}

string Dimensionality::to_string() const
{
    return pImpl->to_string();
}

Dimensionality Dimensionality::multiply(const Dimensionality& other) const
{
    return Dimensionality(pImpl->multiply(*other.pImpl));
}

} // namespace quantity
