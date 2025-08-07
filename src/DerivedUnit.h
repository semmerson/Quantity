/**
 * This file declares a class for derived units (e.g., "kg·m·s-2").
 *
 *        File: DerivedUnit.h
 *  Created on: Aug 4, 2025
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

#pragma once

#include "Unit.h"

namespace quantity {

/// A class for derived units (e.g., watt).
class DerivedUnit : public Unit
{
public:
    /// Constructs
    DerivedUnit() =default;
};


} // namespace quantity
