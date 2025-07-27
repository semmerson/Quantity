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

#ifndef SRC_SCALE_H_
#define SRC_SCALE_H_


namespace quantity {

class Scale
{
public:
    /// Destroys.
    virtual ~Scale() {};

    /**
     * Converts a value.
     * @param[in] value  The value to be converted.
     * @return           The converted value.
     */
    virtual double convert(const double value) =0;
};

}

#endif /* SRC_SCALE_H_ */
