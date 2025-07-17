/**
 * This file declares class `Dimension`.
 *
 *        File: Dimension.h
 *  Created on: Jul 14, 2025
 *      Author: Steven R. Emmerson
 *
 *    Copyright 2025 Steven R. Emmerson, All rights reserved
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

#ifndef MAIN_DIMENSION_H_
#define MAIN_DIMENSION_H_

#include <memory>
#include <string>

using namespace std;

namespace quantity {

/**
 * Interface for a physical dimension (e.g., length, mass).
 */
class Dimension {
public:
	/// Smart pointer to an instance
	using Pimpl = shared_ptr<Dimension>;

	/**
	 * Factory method for creating an instance
	 *
	 * @param name  Name of the dimension (e.g., "length")
	 * @return      Smart pointer to created instance
	 * @throw       std::invalid_argument if the name is empty or the name is
	 *              already in use
	 */
	static Pimpl create(const string&  name);

	/**
	 * Factory method for creating an instance
	 *
	 * @param name  Name of the dimension (e.g., "length")
	 * @return      Smart pointer to created instance
	 * @throw       std::invalid_argument if the name is empty or the name is
	 *              already in use
	 */
	static Pimpl create(string&& name);

	/**
	 * Necessary for separation of interface and implementation.
	 */
	virtual ~Dimension() {};
};

}

#endif /* MAIN_DIMENSION_H_ */
