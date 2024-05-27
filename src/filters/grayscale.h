#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "image/color.h"

#include <filters/filter.h>
#include <filters/registry.h>

namespace image_processor::filters {

class Grayscale : public Filter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (!parameters.empty()) {
                throw std::invalid_argument("");
            }
            return std::make_unique<Grayscale>();
        }
    };

public:
    Grayscale() {
    }

    image::Image Apply(const image::Image& image) override {
        image::Image result_image = image;
        for (size_t i = 0; i < image.GetHeight(); ++i) {
            for (size_t j = 0; j < image.GetWidth(); ++j) {
                float temp = result_image(i, j).r * RedCoeff + result_image(i, j).g * GreenCoeff +
                             result_image(i, j).b * BlueCoeff;
                result_image(i, j).r = temp;
                result_image(i, j).g = temp;
                result_image(i, j).b = temp;
            }
        }
        return result_image;
    }

private:
    static constexpr float RedCoeff = 0.299;
    static constexpr float GreenCoeff = 0.587;
    static constexpr float BlueCoeff = 0.114;
};

}  // namespace image_processor::filters
