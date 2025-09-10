/**
 * This file implements a timestamp.
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
#include "Timestamp.h"

#include "GregorianTimestamp.h"
#include "Unit.h"

#include <string>

using namespace std;

namespace quantity {

Timestamp::Timestamp(const TimestampImpl* impl)
    : pImpl(impl)
{}

Timestamp Timestamp::getGregorian(int    year,
                                  int    month,
                                  int    day,
                                  int    hour,
                                  int    min,
                                  double sec,
                                  int    zone)
{
    return Timestamp(new GregorianTimestamp(year, month, day, hour, min, sec, zone));
}

string Timestamp::to_string() const
{
    return pImpl->to_string();
}

bool Timestamp::isConvertible(const Timestamp& other) const
{
    return pImpl->isConvertible(*pImpl);
}

double Timestamp::subtract(const Timestamp& other, const Unit::Pimpl& unit) const
{
    return pImpl->subtract(*other.pImpl, unit);
}

} // Namespace
