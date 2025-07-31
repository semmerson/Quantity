/**
 * This file implements a class for affine transformations.
 *
 *        File: AffineScale.h
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

#include "AffineScale.h"

#include <stdexcept>
#include <cmath>

namespace quantity {

/**
 * Implementation of an affine scale.
 */
class AffineScaleImpl : public Scale::Impl {
    const double slope;     ///< The slope
    const double intercept; ///< The intercept

public:
    /**
     * Constructs
     * @param[in] slope             The slope
     * @param[in] intercept         The intercept
     */
    AffineScaleImpl(
            const double slope,
            const double intercept)
        : slope{slope}
        , intercept{intercept} {}

    /**
     * Indicates if the origin of this scale is *not* zero.
     * @retval false    The origin of this scale is zero
     * @retval true     The origin of this scale is not zero
     */
    bool isOffset() const override {
        return intercept != 0;
    }

    /**
     * Multiplies by a numeric factor.
     * @param[in] factor    The numeric factor
     * @return              A scale whose transformations are equal to this scale times a factor.
     *                      NB: The intercept will be unchanged (zero kilocelsius is still 273.15
     *                      kelvin).
     */
    AffineScaleImpl* multiply(const double factor) const override {
        return new AffineScaleImpl(factor*slope, intercept);
    }

    /**
     * Divides by a numeric factor.
     * @param[in] factor    The numeric factor
     * @return              A scale whose transformations are equal to this scale divided by a
     *                      factor. NB: The intercept will be unchanged (zero decicelsius is still
     *                      273.15 kelvin).
     */
    AffineScaleImpl* divide(const double factor) const override {
        return new AffineScaleImpl(slope/factor, intercept);
    }

    /**
     * Raises to a numeric power.
     * @param[in] power         The numeric exponent
     * @return                  A scale whose transformations are equal to this scale raised to a
     *                          power
     * @throw std::domain_error The intercept is not zero
     */
    AffineScaleImpl* pow(const int power) const override {
        if (intercept != 0)
            throw std::domain_error("Intercept is not zero");

        return new AffineScaleImpl(std::pow(slope, power), 0);
    }

    /**
     * Takes a root.
     * @param[in] root              The numeric root
     * @return                      A scale whose transformations are equal to this scale taken to a
     *                              root
     * @throw std::invalid_argument The numeric root is not positive
     * @throw std::domain_error     The intercept is not zero
     */
    AffineScaleImpl* root(const int root) const override {
        if (root <= 0)
            throw std::invalid_argument("Numeric root is not positive");
        if (intercept != 0)
            throw std::domain_error("Intercept is not zero");

        return new AffineScaleImpl(std::pow(slope, 1.0/root), 0);
    }

    /**
     * Converts a numeric value.
     * @param[in] value  The value to be transformed
     * @return           The transformed value
     */
    double convert(const double value) const override {
        return slope*value + intercept;
    }
};

AffineScale::AffineScale(
        const double slope,
        const double intercept)
    : Scale(new AffineScaleImpl(slope, intercept)) {}

} // namespace
