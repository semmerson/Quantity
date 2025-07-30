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
     * Converts a numeric value.
     * @param[in] value  The value to be transformed
     * @return           The transformed value
     */
    double convert(const double value) const {
        return slope*value + intercept;
    }

    /**
     * Multiplies by a numeric factor.
     * @param[in] factor    The numeric factor
     * @return              A scale whose transformations are equal to this scale times a factor.
     *                      NB: The intercept will be unchanged (zero kilocelsius is still 273.15
     *                      kelvin).
     */
    AffineScaleImpl* multiply(const double factor) const {
        return new AffineScaleImpl(factor*slope, intercept);
    }
};

AffineScale::AffineScale(
        const double slope,
        const double intercept)
    : Scale(new AffineScaleImpl(slope, intercept)) {}

} // namespace
