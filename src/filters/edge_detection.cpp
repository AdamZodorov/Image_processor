#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include "filters/grayscale.h"
#include "image/color.h"
#include "image/image.h"
#include "utils/matrix.h"

#include <filters/matrix_filter.h>
#include <filters/registry.h>

namespace image_processor::filters {

namespace {

float Cast(std::string_view s) {
    std::stringstream sstream(s.data());
    float result = 0;
    sstream >> result;
    return result;
}

}  // namespace

class EdgeDetection : public MatrixFilter {
public:
    class Factory : public MatrixFilter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (parameters.size() != 1) {
                throw std::invalid_argument("");
            }
            float threshold = Cast(parameters[0]);
            return std::make_unique<EdgeDetection>(threshold);
        }
    };

public:
    explicit EdgeDetection(float threshold) : threshold_{threshold} {
    }
    image::Image Apply(const image::Image& image) override {
        Grayscale gs;
        SetFilterMatrix(filter_matrix_);
        image::Image res = MatrixFilter::Apply(gs.Apply(image));
        for (size_t i = 0; i < res.GetHeight(); ++i) {
            for (size_t j = 0; j < res.GetWidth(); ++j) {
                if (res(i, j).r > threshold_) {
                    res(i, j).b = res(i, j).g = res(i, j).r = 1;
                } else {
                    res(i, j).b = res(i, j).g = res(i, j).r = 0;
                }
            }
        }
        return res;
    }

private:
    utils::Matrix<float> filter_matrix_{{0, -1, 0}, {-1, FilterMatrixValue, -1}, {0, -1, 0}};
    static constexpr int FilterMatrixValue = 4;
    float threshold_;
};

REGISTER_FILTER("edge", EdgeDetection::Factory)

}  // namespace image_processor::filters
