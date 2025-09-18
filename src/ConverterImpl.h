/**
 * This file declares an abstract implementation of a converter of unit values.
 *
 *        File: ConverterImpl.h
 *  Created on: Sep 11, 2025
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

namespace quantity {

/// Interface for converter implementations.
class ConverterImpl
{
public:
    /// Destroys.
	virtual ~ConverterImpl() =default;

	/**
	 * Converts a numeric value in the input unit to the equivalent value in the output unit.
	 * @param[in] value     The numeric value in the input unit
	 * @return              The equivalent numeric value in the output unit
	 */
	virtual double operator()(const double value) const =0;
};

} // namespace quantity
