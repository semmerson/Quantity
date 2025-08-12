/**
 * This file implements a base physical quantity (e.g., length, mass).
 *
 *        File: BaseQuantity.h
 *  Created on: Aug 12, 2025
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

#include "BaseQuantity.h"

namespace quantity {

/// Implementation of a base physical quantity (e.g., length, mass).
class BaseQuantity::Impl
{
private:
    const Dimension dim;
    const BaseUnit  unit;

public:
    /**
     * Constructs.
     * @param[in] dim   Associated dimension (e.g., length)
     * @param[in] unit  Associated base unit (e.g., meter)
     */
    Impl(const Dimension& dim,
         const BaseUnit&  unit)
        : dim(dim)
        , unit(unit)
    {}
};

BaseQuantity::BaseQuantity(Impl* impl)
    : pImpl(impl)
{}

BaseQuantity::BaseQuantity(const Dimension& dim,
                           const BaseUnit&  unit)
    : BaseQuantity(new BaseQuantity::Impl(dim, unit))
{}

} // Namespace
