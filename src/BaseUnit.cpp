/**
 * This file defines a class for a base unit of a physical quantity.
 *
 *        File: BaseUnit.cpp
 *  Created on: Jul 27, 2025
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

#include "BaseUnit.h"

#include "BaseUnitImpl.h"

#include <stdexcept>
#include <cmath>

namespace quantity {

BaseUnit::BaseUnit(
        const Dimension& dim,
        const std::string& name,
        const std::string& symbol)
    : Unit(new BaseUnitImpl(dim, name, symbol))
{}

} // namespace
