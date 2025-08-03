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
class Scale
{
public:
    /// The implementation
    class Impl {
    public:
        virtual ~Impl();

        /**
         * Indicates if the origin of this scale is *not* zero.
         * @retval false    The origin of this scale is zero
         * @retval true     The origin of this scale is not zero
         */
        virtual bool isOffset() const =0;

        /**
         * Multiplies by a numeric factor.
         * @param[in] factor The numeric factor
         * @return           A scale whose transformations are equal to this scale times a factor
         */
        virtual Impl* multiply(const double factor) const =0;

        /**
         * Divides by a numeric factor.
         * @param[in] factor The numeric factor
         * @return           A scale whose transformations are equal to this scale divided by a
         *                   factor
         */
        virtual Impl* divide(const double factor) const =0;

        /**
         * Raises to a numeric power.
         * @param[in] power     The numeric power
         * @return              A scale whose transformations are equal to this scale raised to a
         *                      power.
         */
        virtual Impl* pow(const int power) const =0;

        /**
         * Takes a root.
         * @param[in] root          The numeric root
         * @return                  A scale whose transformations are equal to this scale taken to a
         *                          root.
         * @throw std::domain_error The scale can't have a root taken
         */
        virtual Impl* root(const int root) const =0;

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
     * Indicates if the origin of this scale is *not* zero.
     * @retval false    The origin of this scale is zero
     * @retval true     The origin of this scale is not zero
     */
    bool isOffset() const;

    /**
     * Multiplies by a numeric factor.
     * @param[in] factor    The numeric factor
     * @return              A scale whose transformations are equal to this scale times a factor
     */
    Scale multiply(const double factor) const;

    /**
     * Divides by a numeric factor.
     * @param[in] factor    The numeric factor
     * @return              A scale whose transformations are equal to this scale divided by a
     *                      factor
     */
    Scale divide(const double factor) const;

    /**
     * Raises to a power.
     * @param[in] power     The numeric power
     * @return              A scale whose transformations are equal to this scale raised to a power.
     */
    Scale pow(const int power) const;

    /**
     * Takes a root.
     * @param[in] root          The numeric root
     * @return                  A scale whose transformations are equal to this scale taken to a
     *                          root.
     * @throw std::domain_error The scale can't have a root taken
     */
    Scale root(const int root) const;

    /**
     * Converts a value.
     * @param[in] value  The value to be converted.
     * @return           The converted value.
     */
    double convert(const double value) const;

protected:
    /// Smart pointer to the implementation for automatic deletion
    std::shared_ptr<Impl> pImpl;
};

} // namspace quantity
