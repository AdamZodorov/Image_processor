#include <initializer_list>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "image/color.h"
#include "utils/matrix.h"

#include <filters/matrix_filter.h>
#include <filters/registry.h>

namespace image_processor::filters {

class Sharpering : public MatrixFilter {
public:
    class Factory : public MatrixFilter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (!parameters.empty()) {
                throw std::invalid_argument("");
            }
            return std::make_unique<Sharpering>();
        }
    };

public:
    image::Image Apply(const image::Image& image) override {
        SetFilterMatrix(filter_matrix_);
        return MatrixFilter::Apply(image);
    }

private:
    utils::Matrix<float> filter_matrix_{{0, -1, 0}, {-1, FilterMatrixValue, -1}, {0, -1, 0}};
    static constexpr int FilterMatrixValue = 5;
};

REGISTER_FILTER("sharp", Sharpering::Factory)

}  // namespace image_processor::filters
