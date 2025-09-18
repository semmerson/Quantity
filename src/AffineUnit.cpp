/**
 * This file implements an affine unit of a physical quantity.
 *
 *        File: AffineUnit.h
 *  Created on: Aug 29, 2025
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

#include "AffineUnit.h"
#include "CanonicalUnit.h"
#include "Converter.h"
#include "ConverterImpl.h"
#include "RefLogUnit.h"

namespace quantity {

/// Converter of numeric values in an affine unit to an output unit.
class AffineUnit::ToConverter : public ConverterImpl {
private:
    const Converter coreConverter;
    const double    slope;
    const double    intercept;
public:
    /**
     * Move constructs.
     * @param[in] coreConverter     The core unit's converter to the output unit
     * @param[in] slope             The affine unit's slope parameter
     * @param[in] intercept         The affine unit's intercept parameter
     */
    ToConverter(const Converter&& coreConverter, const double slope, const double intercept)
        : coreConverter(coreConverter)
        , slope(slope)
        , intercept(intercept)
    {}
    double operator()(const double value) const override {
        return coreConverter((value - intercept)/slope);
    }
};

/// Converter of numeric values in an input unit to an affine unit.
class AffineUnit::FromConverter : public ConverterImpl {
private:
    const Converter coreConverter;
    const double    slope;
    const double    intercept;
public:
    /**
     * Move constructs.
     * @param[in] coreConverter     The core unit's converter from the input unit
     * @param[in] slope             The affine unit's slope parameter
     * @param[in] intercept         The affine unit's intercept parameter
     */
    FromConverter(const Converter&& coreConverter, const double slope, const double intercept)
        : coreConverter(coreConverter)
        , slope(slope)
        , intercept(intercept)
    {}
    double operator()(const double value) const override {
        return slope*coreConverter(value) + intercept;
    }
};

AffineUnit::AffineUnit(
        const Pimpl&      core,
        const double      slope,
        const double      intercept)
    : core{core}
    , slope{slope}
    , intercept{intercept}
{
    if (slope == 0)
        throw std::invalid_argument("Slope is zero");
    if (slope == 1 && intercept == 0)
        throw std::invalid_argument("Slope is one and intercept is zero");
}

std::string AffineUnit::to_string() const
{
    string rep{""};
    if (slope != 1) {
        rep += std::to_string(slope) + "*";
    }
    string coreStr = core->to_string();
    const bool haveBlank = coreStr.find(" ") != string::npos;
    if (haveBlank)
        rep += "(";
    rep += coreStr;
    if (haveBlank)
        rep += ")";
    if (intercept < 0) {
        rep += " - " + std::to_string(abs(intercept));
    }
    else if (intercept > 0) {
        rep += " + " + std::to_string(intercept);
    }
    return rep;
}

Unit::Type AffineUnit::type() const
{
    return (slope == 1 && intercept == 0)
            ? core->type()
            : Type::AFFINE;
}

bool AffineUnit::isDimensionless() const
{
    return core->isDimensionless();
}

bool AffineUnit::isOffset() const
{
    return intercept != 0;
}

size_t AffineUnit::hash() const
{
    static auto myHash = std::hash<double>();
    return core->hash() ^ myHash(slope) ^ myHash(intercept);
}

int AffineUnit::compare(const Pimpl& other) const
{
    return -other->compareTo(*this);
}

int AffineUnit::compareTo(const CanonicalUnit& other) const
{
    return 1;   // Affine units come after derived units
}

int AffineUnit::compareTo(const AffineUnit& other) const
{
    int cmp = core->compare(other.core);
    if (cmp != 0)
        return cmp;
    cmp = slope < other.slope
            ? -1
            : slope > other.slope
              ? 1
              : 0;
    if (cmp != 0)
        return cmp;
    return intercept < other.intercept
            ? -1
            : intercept > other.intercept
              ? 1
              : 0;
}

int AffineUnit::compareTo(const RefLogUnit& other) const
{
    return -1;  // Affine units come before log units
}

bool AffineUnit::isConvertible(const Pimpl& other) const
{
    return other->isConvertibleTo(*this);
}

bool AffineUnit::isConvertibleTo(const CanonicalUnit& other) const
{
    return core->isConvertibleTo(other);
}

bool AffineUnit::isConvertibleTo(const AffineUnit& other) const
{
    return core->isConvertible(other.core);
}

bool AffineUnit::isConvertibleTo(const RefLogUnit& other) const
{
    return other.isConvertibleTo(*this); // Defer to the other unit
}

Converter AffineUnit::getConverterTo(const Pimpl& output) const
{
    if (!isConvertible(output))
        throw invalid_argument("Units are not convertible");

    return Converter(new ToConverter(core->getConverterTo(output), slope, intercept));
}

Converter AffineUnit::getConverterFrom(const CanonicalUnit& input) const
{
    if (!isConvertibleTo(input))
        throw invalid_argument("Units are not convertible");

    return Converter(new FromConverter(core->getConverterFrom(input), slope, intercept));
}

Converter AffineUnit::getConverterFrom(const AffineUnit& input) const
{
    if (!isConvertibleTo(input))
        throw invalid_argument("Units are not convertible");

    return Converter(new FromConverter(core->getConverterFrom(input), slope, intercept));
}

Converter AffineUnit::getConverterFrom(const RefLogUnit& input) const
{
    if (!isConvertibleTo(input))
        throw invalid_argument("Units are not convertible");

    return Converter(new FromConverter(core->getConverterFrom(input), slope, intercept));
}

Unit::Pimpl AffineUnit::multiply(const Pimpl& other) const
{
    return other->multiplyBy(*this);
}

Unit::Pimpl AffineUnit::multiplyBy(const CanonicalUnit& other) const
{
    if (intercept != 0)
        throw std::logic_error("Multiplication by an offset unit isn't supported");

    return get(core->multiplyBy(other), slope, 0);
}

Unit::Pimpl AffineUnit::multiplyBy(const AffineUnit& other) const
{
    if (intercept != 0 || other.intercept != 0)
        throw std::logic_error("Multiplication by an offset unit isn't supported");

    return get(core->multiply(other.core), slope*other.slope, 0);
}

Unit::Pimpl AffineUnit::pow(const Exponent exp) const
{
    if (intercept != 0)
        throw std::logic_error("Exponentiating an offset unit isn't supported");

    return get(core->pow(exp), exp.exponentiate(slope), 0);
}

} // Namespace
