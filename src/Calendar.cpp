/**
 * This file implements class Calendar
 *
 *        File: Calendar.cpp
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
#include "Calendar.h"

#include "GregorianCalendar.h"

namespace quantity {

Calendar::Calendar(CalendarImpl* impl)
    : pImpl(impl)
{}

Calendar Calendar::getGregorian()
{
    return Calendar(new GregorianCalendar());
}

bool Calendar::isConvertible(const Calendar& other) const
{
    return pImpl->isConvertible(*other.pImpl);
}

} // Namespace
