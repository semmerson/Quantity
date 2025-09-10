/**
 * This file defines a base class for concrete implementation of a timestamp.
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

#include "Calendar.h"
#include "Timestamp.h"
#include "Unit.h"

using namespace std;

namespace quantity {

/// Base class for concrete implementations of a timestamp.
class TimestampImpl
{
private:
    Calendar calendar;  ///< Calendar on which this timestamp is based

protected:
    /**
     * Constructs from a calendar
     * @param[in] calendar  The calendar on which this timestamp is based
     */
    TimestampImpl(Calendar calendar);

public:
    virtual ~TimestampImpl() =default;

    /**
     * Returns a string representation of this instance.
     * @return A string representation of this instance
     */
    virtual string to_string() const =0;

    /**
     * Indicates if this instance is convertible with another.
     * @param[in] other     Other instance
     * @retval    true      This instance is convertible with the other
     * @retval    false     This instance is not convertible with the other
     */
    virtual bool isConvertible(const TimestampImpl& other) const =0;

    /**
     * Returns the time interval from another instance to this instance in a given unit.
     * @param other                     Other instance
     * @param unit                      Desired unit for result
     * @return                          Time interval from another instance to this instance in the
     *                                  given unit
     * @throw std::invalid_argument     The two instances are not convertible
     * @throw std::invalid_argument     The unit isn't a temporal unit
     */
    virtual double subtract(const TimestampImpl& other, const Unit::Pimpl& unit) const =0;
};

} // Namespace
