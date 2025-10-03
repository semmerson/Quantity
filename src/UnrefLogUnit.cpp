/**
 * This file implements a logarithmic unit without a reference level.
 *
 *        File: UnrefLogUnit.cpp
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

#include "UnrefLogUnit.h"

#include "AffineUnit.h"
#include "CanonicalUnit.h"
#include "Converter.h"
#include "ConverterImpl.h"
#include "Dimensionality.h"

#include <cfloat>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

namespace quantity {

/// Converter of numeric values in an input unit to an unreferenced logarithmic unit.
class UnrefLogUnit::FromConverter : public ConverterImpl {
private:
    const double    inputLogBase;   ///< Natural logarithm of the input unit's base
    const double    outputLogBase;  ///< Natural logarithm of the output unit's base
public:
    /**
     * Constructs.
     * @param[in] inputLogBase      Natural logarithm of the input unit's base
     * @param[in] outputLogBase     Natural logarithm of the output unit's base
     */
    FromConverter(const double inputLogBase, const double outputLogBase)
        : inputLogBase(inputLogBase)
        , outputLogBase(outputLogBase)
    {}
    double operator()(const double value) const override {
        return value*(inputLogBase/outputLogBase);
    }
};

UnrefLogUnit::UnrefLogUnit(const BaseEnum         base,
                           const Dimensionality& dims)
    : LogUnit(base)
    , dims(dims)
{};

string UnrefLogUnit::to_string() const
{
    string rep;

    switch (baseEnum) {
        case BaseEnum::TWO: {rep += "lb"; break;}
        case BaseEnum::E:   {rep += "ln"; break;}
        case BaseEnum::TEN: {rep += "lg"; break;}
        default: throw std::logic_error("Unsupported logarithmic base");
    }
    const auto isCompound = dims.size() > 1;
    rep += "(";
    if (isCompound)
        rep += "(";
    rep += dims.to_string();
    if (isCompound)
        rep += ")";
    rep += "^0)";

    return rep;
}

Unit::Type UnrefLogUnit::type() const
{
    return Type::UNREF_LOG;
}

bool UnrefLogUnit::isDimensionless() const
{
    return true;
}

bool UnrefLogUnit::isOffset() const
{
    return false;   // Logarithmic units are logarithms of ratios, so can't be offset
}

size_t UnrefLogUnit::hash() const
{
    return std::hash<int>()(static_cast<int>(baseEnum));
}

int UnrefLogUnit::compare(const Pimpl& other) const
{
    return -other->compareTo(*this);
}

int UnrefLogUnit::compareTo(const CanonicalUnit& other) const
{
    return 1;
}

int UnrefLogUnit::compareTo(const AffineUnit& other) const
{
    return 1;  // Affine units come before unreferenced logarithmic units
}

int UnrefLogUnit::compareTo(const RefLogUnit& other) const
{
    return 1;
}

int UnrefLogUnit::compareTo(const UnrefLogUnit& other) const
{
    return (logBase < other.logBase)
            ? -1
            : (logBase > other.logBase)
              ? 1
              : dims.compare(other.dims);
}

bool UnrefLogUnit::isConvertible(const Pimpl& other) const
{
    return other->isConvertibleTo(*this);
}

bool UnrefLogUnit::isConvertibleTo(const CanonicalUnit& other) const
{
    return false;
}

bool UnrefLogUnit::isConvertibleTo(const AffineUnit& other) const
{
    return false;
}

bool UnrefLogUnit::isConvertibleTo(const RefLogUnit& other) const
{
    return false;
}

bool UnrefLogUnit::isConvertibleTo(const UnrefLogUnit& other) const
{
    return true;
}

Converter UnrefLogUnit::getConverterTo(const Pimpl& output) const
{
    return output->getConverterFrom(*this);
}

Converter UnrefLogUnit::getConverterFrom(const CanonicalUnit& input) const
{
    throw invalid_argument("Units are not convertible");
}

Converter UnrefLogUnit::getConverterFrom(const AffineUnit& input) const
{
    throw invalid_argument("Units are not convertible");
}

Converter UnrefLogUnit::getConverterFrom(const RefLogUnit& input) const
{
    throw invalid_argument("Units are not convertible");
}

Converter UnrefLogUnit::getConverterFrom(const UnrefLogUnit& input) const
{
    return Converter(new FromConverter(input.logBase, logBase));
}

} // Namespace
