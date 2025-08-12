/**
 * This file implements an affine unit of a physical quantity
 *
 *        File: AffineUnit.cpp
 *  Created on: Jul 27, 2025
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

#include "AffineUnitImpl.h"

#include "BaseUnitImpl.h"

#include <string>

namespace quantity {

/**
 * Returns a string representation
 * @retval A string representation
 */
std::string AffineUnitImpl::to_string() const
{
    return std::to_string(slope) + "(" + parent->to_string() + ")" + std::to_string(intercept);
}

/**
 * Indicates if numeric values in this unit are convertible with a base unit.
 * @param[in] other The other unit
 * @retval    true  They are convertible
 * @retval    false They are not convertible
 */
bool AffineUnitImpl::isConvertible(const BaseUnitImpl& other) const {
    return parent->isConvertible(other);
}

/**
 * Indicates if numeric values in this unit are convertible with an affine unit.
 * @param[in] other The other unit
 * @retval    true  They are convertible
 * @retval    false They are not convertible
 */
bool AffineUnitImpl::isConvertible(const AffineUnitImpl& other) const {
    return parent->isConvertible(*other.parent);
}

/**
 * Constructs
 * @param[in] parent    The underlying unit from which this unit is derived
 * @param[in] slope     The slope
 * @param[in] intercept The intercept
 */
AffineUnitImpl::AffineUnitImpl(
        const UnitImpl&   parent,
        const double      slope,
        const double      intercept)
    : parent{&parent}
    , slope{slope}
    , intercept{intercept} {}

/**
 * Indicates if this unit is dimensionless.
 * retval true      This unit is dimensionless
 * retval false     This unit is not dimensionless
 */
bool AffineUnitImpl::isDimensionless() const {
    return parent->isDimensionless();
}

/**
 * Indicates if the origin of this scale is *not* zero.
 * @retval false    The origin of this scale is zero
 * @retval true     The origin of this scale is not zero
 */
bool AffineUnitImpl::isOffset() const {
    return intercept != 0;
}

/**
 * Indicates if numeric values in this unit are convertible with another unit.
 * @param[in] other The other unit
 * @retval    true  They are convertible
 * @retval    false They are not convertible
 */
bool AffineUnitImpl::isConvertible(const UnitImpl& other) const {
    return other.isConvertible(*this);
}

/**
 * Converts a numeric value.
 * @param[in] value  The value to be transformed
 * @return           The transformed value
 */
double AffineUnitImpl::convert(const double value) const {
    return slope*value + intercept;
}

/**
 * Multiplies by another unit.
 * @param[in] unit   The other unit
 * @return           A unit whose scale-transform is equal to this unit's times the other unit's
 */
UnitImpl* AffineUnitImpl::multiply(const UnitImpl* unit) const
{
    throw std::logic_error("Not implemented yet");
}

#if 0
/**
 * Multiplies by another unit.
 * @param[in] other  The other unit
 * @return           A unit whose scale-transformation is equal to this unit's times the
 *                   other unit's
 */
UnitImpl* AffineUnitImpl::multiply(const UnitImpl* other) const {
    return other->multiply(this);
}

/**
 * Divides by a numeric factor.
 * @param[in] factor    The numeric factor
 * @return              A scale whose transformations are equal to this scale divided by a
 *                      factor. NB: The intercept will be unchanged (zero decicelsius is still
 *                      273.15 kelvin).
 */
AffineUnitImpl* AffineUnitImpl::divideBy(const double factor) const {
    return new AffineUnitImpl(slope/factor, intercept);
}

/**
 * Divides by another unit.
 * @param[in] other             The other unit
 * @return                      A unit whose scale-transform is equal to this unit's divided by
 *                              the other unit's
 * @throw std::domain_error     This unit's intercept is not zero
 */
UnitImpl* AffineUnitImpl::divideBy(const UnitImpl* other) const {
    if (intercept != 0)
        throw std::domain_error("Intercept is not zero");

    return other->divideInto(this);
}

/**
 * Raises to a numeric power.
 * @param[in] power         The numeric exponent
 * @return                  A scale whose transformations are equal to this scale raised to a
 *                          power
 * @throw std::domain_error The intercept is not zero
 */
AffineUnitImpl* AffineUnitImpl::pow(const int power) const {
    if (intercept != 0)
        throw std::domain_error("Intercept is not zero");

    return new AffineUnitImpl(std::pow(slope, power), 0);
}

/**
 * Takes a root.
 * @param[in] root              The numeric root
 * @return                      A scale whose transformations are equal to this scale taken to a
 *                              root
 * @throw std::invalid_argument The numeric root is not positive
 * @throw std::domain_error     The intercept is not zero
 */
AffineUnitImpl* AffineUnitImpl::root(const int root) const {
    if (root <= 0)
        throw std::invalid_argument("Numeric root is not positive");
    if (intercept != 0)
        throw std::domain_error("Intercept is not zero");

    return new AffineUnitImpl(std::pow(slope, 1.0/root), 0);
}

/**
 * Divides into a base unit.
 * @param[in] other             The base unit
 * @return                      A unit whose scale-transform is equal to this unit's divided
 *                              into the affine unit's
 * @throw std::domain_error     The intercept is not zero
 */
UnitImpl* AffineUnitImpl::divideInto(const BaseUnitImpl* other) const {
    if (intercept != 0)
        throw std::domain_error("The intercept is not zero");

    return new AffineUnitImpl(other->divideBy(parent), 1/slope, 0);
}

/**
 * Divides into an affine unit.
 * @param[in] unit              The affine unit
 * @return                      A unit whose scale-transform is equal to this unit's divided
 *                              into the affine unit's
 * @throw std::domain_error     The intercept is not zero
 */
UnitImpl* AffineUnitImpl::divideInto(const AffineUnitImpl* other) const {
    if (intercept != 0)
        throw std::domain_error("The intercept is not zero");

    return new AffineUnitImpl(other->parent->divideBy(parent), other->slope/slope, 0);
}
#endif

} // namespace
