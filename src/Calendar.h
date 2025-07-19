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
 * Abstract calendar class.
 */
class Calendar {
public:
    using Pimpl = shared_ptr<Calendar>; ///< Smart pointer to an implementation

    /// Abstract timestamp class.
    class Timestamp {
    public:
        virtual ~Timestamp() noexcept;

        virtual long double subtract(const Timestamp& other) =0;
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

    /**
     * Returns the difference, in seconds, between two times.
     */
    virtual long double difference(const Timestamp& lhs, const Timestamp& rhs);
};

}

#endif /* SRC_CALENDAR_H_ */
