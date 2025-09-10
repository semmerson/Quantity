/**
 * This file declares a Gregorian timestamp.
 *
 *        File: GregorianTimestamp.h
 *  Created on: Sep 7, 2025
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

#include "TimestampImpl.h"

#include <string>

using namespace std;

namespace quantity {

/// A timestamp based on the Gregorian calendar
class GregorianTimestamp final : public TimestampImpl
{
private:
    const int    year;  ///< Year
    const int    month; ///< Month (1 - 12)
    const int    day;   ///< Day of month (1 - 31)
    const int    hour;  ///< Hour (0 - 23)
    const int    min;   ///< Minute (0 - 59)
    const double sec;   ///< Second (0 - 61)
    const int    zone;  ///< Timezone in minutes (-720 - 720)

public:
    /**
     * Constructs.
     * @param[in] year      Year
     * @param[in] month     Month (1 - 12)
     * @param[in] day       Day of month (1 - 31)
     * @param[in] hour      Hour (0 - 23)
     * @param[in] min       Minute (0 - 59)
     * @param[in] sec       Second (0 - 61)
     * @param[in] zone      Time zone in minutes (-720 - 720)
     */
    GregorianTimestamp(const int    year,
                       const int    month,
                       const int    day,
                       const int    hour,
                       const int    min,
                       const double sec,
                       const int    zone = 0);

    /**
     * Returns a string representation of this instance.
     * @return A string representation of this instance
     */
    string to_string() const override;

    /**
     * Indicates if this instance is convertible with another.
     * @param[in] other     Other instance
     * @retval    true      This instance is convertible with the other
     * @retval    false     This instance is not convertible with the other
     */
    bool isConvertible(const TimestampImpl& other) const override;

    /**
     * Returns the time interval from another instance to this instance in a given unit.
     * @param other                     Other instance
     * @param unit                      Desired unit for result
     * @return                          Time interval from another instance to this instance in the
     *                                  given unit
     * @throw std::invalid_argument     The two instances are not convertible
     * @throw std::invalid_argument     The unit isn't a temporal unit
     */
    double subtract(const TimestampImpl& other, const Unit::Pimpl& unit) const override;
};

} // namespace quantity
