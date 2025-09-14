/**
 * This file declares an abstract converter of numeric values from one unit to another.
 *
 *        File: Converter.h
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

#include <memory>

using namespace std;

namespace quantity {

class ConverterImpl;

/// Converter of numeric values in an input unit to the equivalent values in an output unit.
class Converter
{
public:
	using Pimpl = shared_ptr<ConverterImpl>;	///< Type of smart pointer to an implementation

	Pimpl pImpl;					            ///< Smart pointer to an implementation

	/**
	 * Constructs from a pointer to an implementation, for which it assumes responsibility for
	 * deleting when it is no longer used.
	 * @param[in] impl  Pointer to an implementation. Deleted by this class's destructor.
	 */
	Converter(ConverterImpl* impl);

	/**
	 * Converts a numeric value.
	 * @param[in] value     Numeric value in the old unit
	 * @return              Equivalent numeric value in the new unit
	 */
	double convert(const double value) const;

	// Add more conversion methods here (i.e., conversion or arrays, iterators, etc.).
};

} // namespace quantity
