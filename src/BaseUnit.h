/**
 * This file declares a class for base units of physical quantities.
 *
 *        File: BaseUnit.h
 *  Created on: Jul 31, 2025
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

#include "Dimension.h"

#include <memory>
#include <string>

namespace quantity {

using namespace std;

/// Class for base units of physical quantities.
class BaseUnit : public Unit
{
private:
    /// The implementation class.
    class Impl;

    /// Smart pointer to an implementation
    shared_ptr<Impl> pImpl;

protected:

public:
    BaseUnit() =default;

    /**
     * Constructs from a pointer to an implementation.
     * @param[in] impl  Pointer to an implementation
     */
    BaseUnit(Impl* impl);

    /**
     * Constructs.
     * @param[in] dim     Associated dimension
     * @param[in] name    Unit name
     * @param[in] symbol  Unit symbol
     */
    BaseUnit(const Dimension& dim, const std::string& name, const std::string& symbol);
};

} // Namespace
