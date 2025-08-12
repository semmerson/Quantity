/**
 * This file declares a set of dimensions for a physical quantity.
 *
 *        File: Dimensionality.h
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

#pragma once

#include "DimSetImpl.h"

#include <memory>

using namespace std;

namespace quantity {

/// A set of dimensions (alias base quantities) for a physical quantity.
class DimSet
{
private:
    /// Type of PIMPL smart pointer
    using Pimpl = shared_ptr<DimSetImpl>;

    /// Smart pointer to the implementation for automatic deletion
    Pimpl pImpl;

public:
    DimSet() =default;

    /**
     * Constructs from a pointer to an implementation.
     * @param[in] impl  Pointer to an implementation
     */
    DimSet(DimSetImpl* impl);
};

} // namespace quantity
