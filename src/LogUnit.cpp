/**
 * This file implements an abstract logarithmic unit.
 *
 *        File: LogUnit.cpp
 *  Created on: Sep 14, 2025
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

#include "LogUnit.h"

#include <cfloat>
#include <cmath>
#include <stdexcept>

using namespace std;

namespace quantity {

LogUnit::LogUnit(const Base baseEnum)
    : baseEnum(baseEnum)
    , logBase(baseEnum == Base::E ? 1 : baseEnum == Base::TWO ? log(2) : log(10))
{};

LogUnit::~LogUnit() =default;

Unit::Pimpl LogUnit::multiply(const Pimpl& other) const
{
    throw logic_error("Multiplication of a logarithmic unit is not supported");
}

Unit::Pimpl LogUnit::multiplyBy(const CanonicalUnit& other) const
{
    throw logic_error("Multiplication of a logarithmic unit is not supported");
}

Unit::Pimpl LogUnit::multiplyBy(const AffineUnit& other) const
{
    throw logic_error("Multiplication of a logarithmic unit is not supported");
}

Unit::Pimpl LogUnit::pow(const Exponent exp) const
{
    throw logic_error("Exponentiation of a logarithmic unit is not supported");
}

} // Namespace
