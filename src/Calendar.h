/**
 * This file declares an interface for calendars.
 *
 *        File: Calendar.h
 *  Created on: Jul 17, 2025
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

class CalendarImpl;

/**
 * Calendar interface.
 */
class Calendar
{
private:
    Calendar(CalendarImpl* impl);

public:
    using Pimpl = shared_ptr<CalendarImpl>; ///< Type of smart pointer to calendar implementations

    Pimpl pImpl;                            ///< Smart pointer to a calendar implementation

    /**
     * Returns a Gregorian calendar.
     * @return A Gregorian calendar
     */
    static Calendar getGregorian();

    /**
     * Indicates if times in this calendar are convertible with another.
     * @param[in] other     Other calendar
     * @retval    true      Times in this calendar are convertible with the other
     * @retval    false     Times in this calendar are not convertible with the other
     */
    bool isConvertible(const Calendar& other) const;
};

} // Namespace
