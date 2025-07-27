/**
 * This file implements a class for affine conversions.
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
 * Class for affine conversions.
 */
class AffineScale::Impl
{
    const double slope;     ///< The slope
    const double intercept; ///< The intercept

public:
    Impl(
            const double slope,
            const double intercept)
        : slope{slope}
        , intercept{intercept}
    {}

    double convert(const double value)
    {
        return slope*value + intercept;
    }
};

AffineScale::AffineScale(
        const double slope,
        const double intercept)
    : pImpl{new AffineScale::Impl(slope, intercept)}
{}

double AffineScale::convert(const double value)
{
    return pImpl->convert(value);
}

}
