#include <initializer_list>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "image/color.h"

#include <filters/filter.h>
#include <filters/registry.h>

namespace image_processor::filters {

class Negative : public Filter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (!parameters.empty()) {
                throw std::invalid_argument("");
            }
            return std::make_unique<Negative>();
        }
    };

public:
    Negative() {
    }

    image::Image Apply(const image::Image& image) override {
        image::Image result_image = image;
        for (size_t i = 0; i < image.GetHeight(); ++i) {
            for (size_t j = 0; j < image.GetWidth(); ++j) {
                result_image(i, j).r = 1 - result_image(i, j).r;
                result_image(i, j).g = 1 - result_image(i, j).g;
                result_image(i, j).b = 1 - result_image(i, j).b;
            }
        }
        return result_image;
    }
};

REGISTER_FILTER("neg", Negative::Factory)

}  // namespace image_processor::filters
