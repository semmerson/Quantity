/**
 * This file implements a class for converting numeric values.
 *
 *        File: Scale.h
 *  Created on: Jul 28, 2025
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

#include "Scale.h"

namespace quantity {

Scale::Impl::~Impl() {}

Scale::Scale(Impl* impl)
    : pImpl(impl) {
}

bool Scale::isOffset() const {
    return pImpl->isOffset();
}

double Scale::convert(const double value) const {
    return pImpl->convert(value);
}

Scale Scale::multiply(const double factor) const {
    return Scale(pImpl->multiply(factor));
}

Scale Scale::divide(const double factor) const {
    return Scale(pImpl->divide(factor));
}

Scale Scale::pow(const int power) const {
    return Scale(pImpl->pow(power));
}

Scale Scale::root(const int root) const {
    return Scale(pImpl->root(root));
}

}
