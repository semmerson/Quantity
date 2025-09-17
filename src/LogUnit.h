/**
 * This file declares an abstract logarithmic unit.
 *
 *        File: LogUnit.h
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
#pragma once

#include "Unit.h"

namespace quantity {

/// Abstract logarithmic unit.
class LogUnit : public Unit
{
public:
    /// Logarithmic base enumeration
    enum class Base {
        TWO,    ///< Binary logarithm
        E,      ///< Natural logarithm
        TEN     ///< Common logarithm
    };

protected:
    const Base   baseEnum;  ///< Logarithmic base enumeration
    const double logBase;   ///< Natural logarithm of the base

    /**
     * Constructs from a logarithmic base.
     * @param[in] base  The logarithmic base
     */
    LogUnit(const Base base);

public:
    /// Destroys.
    virtual ~LogUnit() =0;

    /**
     * Multiplies by another unit.
     * @param[in] unit              The other unit
     * @return                      A unit whose scale-transform is equal to this unit's times the other unit's
     * @throw     std::logic_error  Multiplication isn't supported
     */
    Pimpl multiply(const Pimpl& unit) const override;

    /**
     * Multiplies by a derived unit.
     * @param[in] other             The derived unit
     * @return                      A unit whose scale-transform is equal to this unit's times the other unit's
     * @throw     std::logic_error  Multiplication isn't supported
     */
    Pimpl multiplyBy(const CanonicalUnit& other) const override;

    /**
     * Multiplies by an affine unit.
     * @param[in] other             The affine unit
     * @return                      A unit whose scale-transform is equal to this unit's times the other unit's
     * @throw     std::logic_error  Multiplication isn't supported
     */
    Pimpl multiplyBy(const AffineUnit& other) const override;

    /**
     * Returns this instance raised to a power in a new unit.
     * @param[in] exp   The exponent
     * @return          The result
     * @throw     std::logic_error  Exponentiation of a logarithmic unit isn't supported
     */
    Pimpl pow(const Exponent exp) const override;
};

} // namespace quantity
