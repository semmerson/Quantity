/**
 * This file declares a base physical quantity (e.g., length, mass).
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

#pragma once

#include "Unit.h"
#include "Dimension.h"

#include <memory>
#include <string>

namespace quantity {

/// A base physical quantity (e.g., length, mass).
class BaseQuantity
{
public:
	using Pimpl = shared_ptr<BaseQuantity>;    ///< Smart pointer to an implementation

	/// Default constructs.
	BaseQuantity() =default;

	/// Destroys.
	virtual ~BaseQuantity() noexcept =0;

    /**
     * Returns an instance. Creates the instance if it doesn't already exist.
     * @param[in] dim   Associated dimension (e.g., length)
     * @param[in] unit  Associated base unit (e.g., meter)
     */
    static Pimpl get(const Dimension&    dim,
                     const Unit::Pimpl&  unit);

    /**
     * Returns the associated physical dimension.
     * @return The associated physical dimension
     */
    virtual const Dimension& dimension() const noexcept =0;

    /**
     * Returns the associated base unit.
     * @return The associated base unit
     */
    virtual const BaseUnit& baseUnit() const noexcept =0;
};

} // namespace quantity
