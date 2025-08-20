/**
 * This file implements the dimensionality of a physical quantity.
 *
 *        File: DimensionalityImpl.h
 *  Created on: Aug 19, 2025
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

#include "DimensionalityImpl.h"

using namespace std;

namespace quantity {

DimensionalityImpl::DimensionalityImpl(const Dimension dim,
                                       const int       numer,
                                       const int       denom)
{
    factors.insert(DimFactor(dim, numer, denom));
}

string DimensionalityImpl::to_string() const
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

DimensionalityImpl* DimensionalityImpl::multiply(const DimensionalityImpl& other) const
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
    auto iter = larger->begin();
    newImpl->factors.insert(iter, larger->end());

    for (const auto factor : *smaller) {
        iter = larger->find(factor);
        if (iter == larger->end()) {
            newImpl->factors.insert(*iter);
        }
        else {
            newImpl->factors.insert(iter->pow(factor.getNumer(), factor.getDenom()));
        }
    }

    return newImpl;
}

} // Namespace
