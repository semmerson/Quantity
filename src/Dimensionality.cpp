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

#include "DimFactor.h"
#include "Dimensionality.h"
#include "DimensionalityImpl.h"

#include <memory>

namespace quantity {

using namespace std;

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
