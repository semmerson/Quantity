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

/// A date-timestamp.
class Timestamp {
private:
    /**
     * Constructs from a pointer to an implementation.
     * @param[in] impl  Pointer to an implementation
     */
    Timestamp(const TimestampImpl* impl);

public:
    using Pimpl = shared_ptr<const TimestampImpl>;  ///< Type of smart pointer to implementation

    Pimpl pImpl;                                    ///< Smart pointer to an implementation

    /**
     * Returns a timestamp based on the Gregorian calendar.
     * @param[in] year              Year
     * @param[in] month             Month (1 - 12)
     * @param[in] day               Day of month (1 - 31)
     * @param[in] hour              Hour (0 - 23)
     * @param[in] min               Minute (0 - 59)
     * @param[in] sec               Second (0 - 61)
     * @param[in] zone              Time zone in minutes (-720 - 720)
     * @throw std::invalid_argument Invalid Gregorian time
     */
    static Timestamp getGregorian(int    year,
                                  int    month,
                                  int    day,
                                  int    hour,
                                  int    min,
                                  double sec,
                                  int    zone = 0);

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
