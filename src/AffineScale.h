/**
 * This file declares a class for affine scales (i.e., y = ax + b).
 */

#pragma once

#include "Scale.h"

namespace quantity {

/// Class for affine scales (i.e, y = ax + b).
class AffineScale : public Scale {
public:
    /**
     * Constructs.
     * @param[in] slope             The slope
     * @param[in] intercept         The intercept
     */
    AffineScale(
            const double slope,
            const double intercept);
};

}
