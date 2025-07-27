/**
 * This file declares a class for affine conversions (i.e., y = ax + b).
 */

#ifndef SRC_AFFINESCALE_H_
#define SRC_AFFINESCALE_H_

#include "Scale.h"

#include <memory>

namespace quantity {

class AffineScale : public Scale
{
private:
    /// The implementation
    class Impl;

    /// Smart pointer to the implementation for automatic deletion
    std::shared_ptr<Impl> pImpl;

public:
    /**
     * Constructs.
     * @param[in] slope             The slope
     * @param[in] intercept         The intercept
     */
    AffineScale(
            const double slope,
            const double intercept);

    /**
     * Converts a value.
     * @param[in] value  The value to be converted
     * @return           The converted value
     */
    double convert(const double value);
};

}

#endif /* SRC_AFFINESCALE_H_ */
