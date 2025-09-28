/**
 * This file implements a logarithmic unit with a reference level.
 *
 *        File: RefLogUnit.cpp
 *  Created on: Sep 14, 2025
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

#include "RefLogUnit.h"

#include "AffineUnit.h"
#include "CanonicalUnit.h"
#include "Converter.h"
#include "ConverterImpl.h"

#include <cfloat>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

namespace quantity {

/// Converter of numeric values in a referenced logarithmic unit to an output unit.
class RefLogUnit::ToConverter : public ConverterImpl {
private:
    const Converter refConverter;   ///< The reference level's converter
    const double    logBase;        ///< Natural logarithm of the logarithmic base

public:
    /**
     * Move constructs.
     * @param[in] refConverter  Reference level's converter to the output unit
     * @param[in] logBase       Natural logarithm of the logarithmic base
     */
    ToConverter(const Converter&& refConverter, const double logBase)
        : refConverter(refConverter)
        , logBase(logBase)
    {}
    double operator()(const double value) const override {
        return refConverter(exp(value*logBase));
    }
};

/// Converter of numeric values in an input unit to a referenced logarithmic unit.
class RefLogUnit::FromConverter : public ConverterImpl {
private:
    const Converter refConverter;   ///< The reference level's converter
    const double    logBase;        ///< Natural logarithm of the logarithmic base
public:
    /**
     * Move constructs.
     * @param[in] refConverter  Reference level's converter from the input unit
     * @param[in] logBase       Natural logarithm of the logarithmic base
     */
    FromConverter(const Converter&& refConverter, const double logBase)
        : refConverter(refConverter)
        , logBase(logBase)
    {}
    double operator()(const double value) const override {
        return log(refConverter(value))/logBase;
    }
};

RefLogUnit::RefLogUnit(const Pimpl&  ref,
                       const BaseEnum base)
    : LogUnit(base)
    , refLevel(ref)
{
    if (refLevel->isOffset())
        throw std::logic_error("Reference level is an offset unit");
};

string RefLogUnit::to_string() const
{
    string rep{};

    switch (baseEnum) {
        case BaseEnum::TWO: {rep += "lb"; break;}
        case BaseEnum::E:   {rep += "ln"; break;}
        default:           {rep += "lg"; break;}
    }

    rep += "(re " + refLevel->to_string() + ")"; // IEC 60027-3 Ed. 3.0 standard

    return rep;
}

Unit::Type RefLogUnit::type() const
{
    return Type::REF_LOG;
}

bool RefLogUnit::isDimensionless() const
{
    return true;
}

bool RefLogUnit::isOffset() const
{
    return false;   // Logarithmic units are logarithms of ratios, so can't be offset
}

size_t RefLogUnit::hash() const
{
    return std::hash<int>()(static_cast<int>(baseEnum)) ^ refLevel->hash();
}

int RefLogUnit::compare(const Pimpl& other) const
{
    return -other->compareTo(*this);
}

int RefLogUnit::compareTo(const CanonicalUnit& other) const
{
    return 1;
}

int RefLogUnit::compareTo(const AffineUnit& other) const
{
    return 1;  // Affine units come before reference logarithmic units
}

int RefLogUnit::compareTo(const RefLogUnit& other) const
{
    auto cmp = refLevel->compareTo(other);
    if (cmp == 0)
        cmp = (logBase < other.logBase)
            ? -1
            : (logBase > other.logBase)
              ? 1
              : 0;
    return cmp;
}

int RefLogUnit::compareTo(const UnrefLogUnit& other) const
{
    return -1;  ///< Referenced log units come before unreferenced ones
}

bool RefLogUnit::isConvertible(const Pimpl& other) const
{
    return refLevel->isConvertible(other);
}

bool RefLogUnit::isConvertibleTo(const CanonicalUnit& other) const
{
    return refLevel->isConvertibleTo(other);
}

bool RefLogUnit::isConvertibleTo(const AffineUnit& other) const
{
    return refLevel->isConvertibleTo(other);
}

bool RefLogUnit::isConvertibleTo(const RefLogUnit& other) const
{
    return refLevel->isConvertible(other.refLevel);
}

bool RefLogUnit::isConvertibleTo(const UnrefLogUnit& other) const
{
    throw std::logic_error("Conversion between referenced and unreferenced log units is not "
            "possible");
}

Converter RefLogUnit::getConverterTo(const Pimpl& output) const
{
    return Converter(new ToConverter(refLevel->getConverterTo(output), logBase));
}

Converter RefLogUnit::getConverterFrom(const CanonicalUnit& input) const
{
    if (!input.isConvertibleTo(*this))
        throw invalid_argument("Units are not convertible");

    return Converter(new FromConverter(input.getConverterTo(refLevel), logBase));
}

Converter RefLogUnit::getConverterFrom(const AffineUnit& input) const
{
    if (!input.isConvertibleTo(*this))
        throw invalid_argument("Units are not convertible");

    return Converter(new FromConverter(input.getConverterTo(refLevel), logBase));
}

Converter RefLogUnit::getConverterFrom(const RefLogUnit& input) const
{
    if (!input.isConvertibleTo(*this))
        throw invalid_argument("Units are not convertible");

    return Converter(new FromConverter(input.getConverterTo(refLevel), logBase));
}

Converter RefLogUnit::getConverterFrom(const UnrefLogUnit& input) const
{
    throw invalid_argument("Units are not convertible");
}

} // Namespace
