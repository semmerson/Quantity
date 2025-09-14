/**
 * This file implements an abstract logarithmic unit.
 *
 *        File: RefLog.cpp
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

#include "RefLogUnit.h"

#include <cfloat>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <string>

using namespace std;

namespace quantity {

RefLogUnit::RefLogUnit(const Pimpl& ref,
                       const double base)
    : LogUnit(base)
    , ref(ref)
{
    if (ref->isOffset())
        throw invalid_argument("The reference level is an offset unit.");
};

string RefLogUnit::to_string() const
{
    string rep{};

    if (base == 10) {
        rep += "log10";
    }
    else if (base == 2) {
        rep += "log2";
    }
    else {
        rep += "log";
    }

    rep += "(ref: \"" + ref->to_string() + "\")";

    if (logBase != 1)
        rep += "/" + std::to_string(logBase);

    return rep;
}

} // Namespace
