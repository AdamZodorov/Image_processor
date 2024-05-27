#include "grayscale.h"

namespace image_processor::filters {

REGISTER_FILTER("gs", Grayscale::Factory)

}  // namespace image_processor::filters
