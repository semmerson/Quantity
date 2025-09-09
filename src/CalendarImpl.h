/**
 * This file declares a base class for calendar implementations.
 *
 *        File: CalendarImpl.h
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

/**
 * Base class for calendar implementations.
 */
class CalendarImpl
{
public:
    virtual ~CalendarImpl() =default;

    /**
     * Indicates if times in this calendar are convertible with another.
     * @param[in] other     Other calendar
     * @retval    true      Times in this calendar are convertible with the other
     * @retval    false     Times in this calendar are not convertible with the other
     */
    virtual bool isConvertible(const CalendarImpl& other) const =0;
};

} // Namespace
