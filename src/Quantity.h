/**
 * This file declares an abstract physical quantity.
 *
 *        File: Quantity.h
 *  Created on: Oct 4, 2025
 *      Author: Steven R. Emmerson
 *
 * Copyright 2025 Steven R. Emmerson. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 */

#pragma once

#include <memory>

using namespace std;

namespace quantity {

class Exponent;
class QuantityImpl;

/// A physical quantity.
class Quantity
{
protected:
	using Pimpl = shared_ptr<QuantityImpl>;	///< Type of smart pointer to an implementation

	Pimpl pImpl;					        ///< Smart pointer to an implementation

public:
    /**
     * Indicates if this instance is dimensionless.
     * @retval true      This instance is dimensionless
     * @retval false     This instance is not dimensionless
     */
    bool isDimensionless() const;

    /**
     * Indicates if this instance is an interval. An interval quantity is the difference between two
     * values of the underlying physical quantity (e.g., time since some start time).
     * @retval true      This instance is an interval
     * @retval false     This instance is not an interval
     */
    bool isInterval() const;

    /**
     * Indicates if values in this instance are convertible with another instance. For example,
     * energy values are not convertible to torque values even though their underlying physical
     * quantities have the same dimensionality.
     * @param[in] other The other instance
     * @retval    true  This instance is convertible with the other instance
     * @retval    false This instance is not convertible with the other instance
     */
    bool isConvertible(const Quantity& other) const;

    /**
     * Returns a new instance that is the sum of this instance and another instance. The type of the
     * result depends on the inputs:
     * | This Instance | Other Instance | Result       | Parent           |
     * | ------------- | -------------- | ------------ | ---------------- |
     * | Interval      | Interval       | Interval     | This instance's  |
     * | Interval      | Non-interval   | Non-interval | Other instance's |
     * | Non-Interval  | Interval       | Non-interval | This instance's  |
     * | Non-Interval  | Non-interval   | Non-interval | This instance's  |
     *
     * @param[in] other         The other instance
     * @return                  A new instance
     * @throw std::logic_error  This operation isn't supported on these operands
     */
    Quantity add(const Quantity& other) const;

    /**
     * Returns a new instance that is this instance minus another instance. The type of the
     * result depends on the inputs:
     * | This Instance | Other Instance | Result       | Parent           |
     * | ------------- | -------------- | ------------ | ---------------- |
     * | Interval      | Interval       | Interval     | This instance's  |
     * | Interval      | Non-interval   | ERROR        | ERROR            |
     * | Non-Interval  | Interval       | Non-interval | This instance's  |
     * | Non-Interval  | Non-interval   | Interval     | This instance's  |
     *
     * @param[in] other         The other instance
     * @return                  A new instance
     * @throw std::logic_error  This operation isn't supported on these operands
     */
    Quantity subtract(const Quantity& other) const;

    /**
     * Returns a new instance that is the product of this instance and another instance. Both this
     * instance and the other instance *must* be non-interval quantities.
     * @param[in] other         The other instance
     * @return                  A new instance
     * @throw std::logic_error  This operation isn't supported on these operands
     */
    Quantity multiply(const Quantity& other) const;

    /**
     * Returns a new instance that is the quotient of this instance divided by another instance.
     * Both this instance and the other instance *must* be non-interval quantities.
     * @param[in] other         The other instance
     * @return                  A new instance
     * @throw std::logic_error  This operation isn't supported on these operands
     */
    Quantity divideBy(const Quantity& other) const;

    /**
     * Returns a new instance that is this instance raised to a power. This instance *must* be a
     * non-interval quantity.
     * @param[in] exp   The exponent
     * @return          A new instance
     */
    Quantity pow(const Exponent& exp) const;
};

} // namespace quantity
