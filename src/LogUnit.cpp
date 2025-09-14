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

LogUnit::LogUnit(const double base)
    : base(base)
    , logBase(0)
{
    if (base <= 1)
        throw invalid_argument("Logarithmic base isn't greater than one.");

    logBase = log(base);
    const auto delta = abs(logBase - 1);
    if (delta <= 2*DBL_EPSILON)
        logBase = 1;
};

LogUnit::~LogUnit() =default;

} // Namespace
