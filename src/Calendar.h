/**
 * This file declares class Calendar.
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

#ifndef SRC_CALENDAR_H_
#define SRC_CALENDAR_H_

#include <memory>

using namespace std;

namespace quantity {

/**
 * Abstract calendar interface.
 */
class Calendar {
public:
    using Pimpl = shared_ptr<Calendar>; ///< Smart pointer to an implementation

    /// A specific time in any calendar
    struct Timestamp {
        int    year;   ///< The year
        int    month;  ///< The month (1 - 12)
        int    day;    ///< The day of the month (1 - 31)
        int    hour;   ///< The hour (0 - 23)
        int    minute; ///< The minute (0 - 59)
        double second; ///< The second (0 - 62)
    };

    /**
     * Returns the Gregorian calendar.
     * @return The Gregorian calendar
     */
    static Pimpl getGregorian();

    /**
     * Destroys.
     */
    virtual ~Calendar() noexcept;

private:
    friend class Temporal;

    /**
     * Returns the difference, in seconds, between two times.
     */
    virtual long double difference(const Timestamp& lhs, const Timestamp& rhs) const =0;
};

}

#endif /* SRC_CALENDAR_H_ */
