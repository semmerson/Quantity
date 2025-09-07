/**
 * This file declares a polymorphic timestamp.
 *
 *        File: Timestamp.h
 *  Created on: Sep 6, 2025
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

#include <memory>

namespace quantity {

using namespace std;

class TimestampImpl;

/// An polymorphic base class for timestamps.
class Timestamp {
public:
    using Pimpl = shared_ptr<TimestampImpl>;    ///< Type of smart pointer to implementation

    Pimpl pImpl;                                ///< Smart pointer to an implementation

    /**
     * Returns a string representation of this instance.
     * @return A string representation of this instance
     */
    string to_string() const;

    /**
     * Indicates if this instance is convertible with another.
     * @param[in] other     Other instance
     * @retval    true      This instance is convertible with the other
     * @retval    false     This instance is not convertible with the other
     */
    bool isConvertible(const Timestamp& other) const;

    /**
     * Returns the time interval from another instance to this instance in a given unit.
     * @param other                     Other instance
     * @param unit                      Desired unit for result
     * @return                          Time interval from another instance to this instance in the
     *                                  given unit
     * @throw std::invalid_argument     The two instances are not convertible
     * @throw std::invalid_argument     The unit isn't a temporal unit
     */
    double subtract(const Timestamp& other, const Unit::Pimpl& unit) const;
};

} // namespace quantity
