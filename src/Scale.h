/**
 * This file declares a class for converting values.
 *
 *        File: Scale.h
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

#pragma once

#include <memory>

namespace quantity {

/// A class for numeric scales.
class Scale {
public:
    /// The implementation
    class Impl {
    public:
        virtual ~Impl();

        /**
         * Converts a numeric value.
         * @param[in] value  The value to be converted
         * @return           The converted value
         */
        virtual double convert(const double value) const = 0;
    };

    Scale() =default;

    /**
     * Constructs from a pointer to an implementation.
     * @param[in] impl   Pointer to an implementation
     */
    Scale(Impl* impl);

    /**
     * Converts a value.
     * @param[in] value  The value to be converted.
     * @return           The converted value.
     */
    double convert(const double value) const;

    /**
     * Consolidates another scale with this one.
     * @param[in] first  The first scale to apply
     * @return           A scale whose conversions are equivalent to converting via the first scale
     *                   and then by this one.
     */
    Scale consolidate(const Scale& first) const;

protected:
    /// Smart pointer to the implementation for automatic deletion
    std::shared_ptr<Impl> pImpl;
};

}
