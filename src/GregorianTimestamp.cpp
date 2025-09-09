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
#include "GregorianTimestamp.h"

#include "Unit.h"

#include <cstdio>
#include <stdexcept>
#include <string>

using namespace std;

namespace quantity {

GregorianTimestamp::GregorianTimestamp(const int    zone,
                                       const int    year,
                                       const int    month,
                                       const int    day,
                                       const int    hour,
                                       const int    min,
                                       const double sec)
    : zone{zone}
    , year{year}
    , month{month}
    , day{day}
    , hour{hour}
    , min{min}
    , sec{sec}
{
    if (zone  < -12 || zone  > 12 ||
        month <   1 || month > 12 ||
        day   <   1 || day   > 31 ||
        hour  <   0 || hour  > 23 ||
        min   <   0 || min   > 59 ||
        sec   <   0 || sec   > 61)
        throw std::invalid_argument("Invalid Gregorian time");
}

string GregorianTimestamp::to_string() const
{
    char buf[80];
    const int zoneHour{zone/60};
    const int zoneMin{abs(zone % 60)};
    snprintf(buf, sizeof(buf), "%d-%02d-%02dT%02d:%02d:%09.6f%+02d:%02d", year, month, day, hour,
            min, sec, zoneHour, zoneMin);
    return std::string(buf);
}

bool GregorianTimestamp::isConvertible(const TimestampImpl& other) const
{
    // TODO
    throw std::logic_error("Not implemented yet");
}

double GregorianTimestamp::subtract(const TimestampImpl& other, const Unit::Pimpl& unit) const
{
    // TODO
    throw std::logic_error("Not implemented yet");
}

} // namespace quantity
