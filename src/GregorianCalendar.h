/**
 * This file declares a Gregorian calendar.
 *
 *        File: Gregorian.h
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

#include "Calendar.h"

using namespace std;

namespace quantity {

/**
 * A Gregorian calendar
 */
class GregorianCalendar final : public Calendar {
public:
    /**
     * Returns a Gregorian calendar
     */
    static Pimpl get();

    /**
     * Indicates if times in this instance are convertible with another calendar.
     * @param[in] other     Other calendar
     * @retval    true      Times in this instance are convertible with the other calendar
     * @retval    false     Times in this instance are not convertible with the other calendar
     */
    bool isConvertible(const Pimpl& other) const override;
};

} // Namespace
