#include <cstddef>
#include <exception>
#include <iostream>
#include "filter.h"
#include "image/color.h"
#include "image/image.h"
#include "utils/matrix.h"

namespace image_processor::filters {

class MatrixFilter : public Filter {
public:
    image::Image Apply(const image::Image& image) override {
        image::Image result_image = image;
        MatrixTransformation(result_image);
        return result_image;
    }
    void SetFilterMatrix(const utils::Matrix<float>& filter_matrix) {
        filter_matrix_ = filter_matrix;
    }

private:
    void MatrixTransformation(image::Image& image) {
        utils::Matrix<image::Color> t_im = GetExtendedImage(image);
        for (size_t i = 1; i < image.GetHeight() + 1; ++i) {
            for (size_t j = 1; j < image.GetWidth() + 1; ++j) {
                image(i - 1, j - 1) =
                    filter_matrix_(0, 0) * t_im(i - 1, j - 1) + filter_matrix_(0, 1) * t_im(i, j - 1) +
                    filter_matrix_(0, 2) * t_im(i + 1, j - 1) + filter_matrix_(1, 0) * t_im(i - 1, j) +
                    filter_matrix_(1, 1) * t_im(i, j) + filter_matrix_(1, 2) * t_im(i + 1, j) +
                    filter_matrix_(2, 0) * t_im(i - 1, j + 1) + filter_matrix_(2, 1) * t_im(i, j + 1) +
                    filter_matrix_(2, 2) * t_im(i + 1, j + 1);
                image(i - 1, j - 1).ToNormalValues();
            }
        }
    }
    image::Image GetExtendedImage(const image::Image& image) {
        image::Image res{image.GetWidth() + 2, image.GetHeight() + 2};
        for (size_t i = 1; i < image.GetHeight() + 1; ++i) {
            for (size_t j = 1; j < image.GetWidth() + 1; ++j) {
                res(i, j) = image(i - 1, j - 1);
            }
        }
        for (size_t j = 0; j < res.GetWidth(); ++j) {
            res(0, j) = res(1, j);
            res(res.GetHeight() - 1, j) = res(res.GetHeight() - 2, j);
        }
        for (size_t i = 0; i < res.GetHeight(); ++i) {
            res(i, 0) = res(i, 1);
            res(i, res.GetWidth() - 1) = res(i, res.GetWidth() - 2);
        }
        return res;
    }

private:
    utils::Matrix<float> filter_matrix_;
};

}  // namespace image_processor::filters
