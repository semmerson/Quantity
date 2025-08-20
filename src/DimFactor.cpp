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

DimFactor::DimFactor(DimFactorImpl* impl)
    : pImpl{impl}
{}

DimFactor::DimFactor(
        const Dimension& dim,
        const int        numer,
        const int        denom)
    : DimFactor(new DimFactorImpl(dim, numer, denom))
{}

string DimFactor::to_string() const
{
    return pImpl->to_string();
}

int DimFactor::compare(const DimFactor& other) const
{
    return pImpl->compare(*other.pImpl);
}

DimFactor DimFactor::multiply(const DimFactor& other) const
{
    return DimFactor(pImpl->multiply(*other.pImpl));
}

} // namespace quantity
