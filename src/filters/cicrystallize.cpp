#include <cfloat>
#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "image/color.h"
#include "image/image.h"

#include <filters/filter.h>
#include <filters/registry.h>

namespace image_processor::filters {

namespace {

struct Point {
    size_t x;
    size_t y;
    Point(size_t x, size_t y) : x(x), y(y) {
    }
};

size_t Cast(std::string_view s) {
    std::stringstream sstream(s.data());
    size_t result = 0;
    sstream >> result;
    return result;
}

}  // namespace

class CICrystallize : public Filter {
public:
    class Factory : public Filter::Factory {
    public:
        std::unique_ptr<Filter> Construct(const std::vector<std::string>& parameters) override {
            if (parameters.size() != 1) {
                throw std::invalid_argument("");
            }
            const size_t cnt_of_figures = Cast(parameters[0]);
            return std::make_unique<CICrystallize>(cnt_of_figures);
        }
    };

public:
    explicit CICrystallize(size_t cnt_of_figures) : cnt_of_figures_(cnt_of_figures) {
    }

    image::Image Apply(const image::Image& image) override {
        std::srand(time(0));
        image::Image result_image(image.GetWidth(), image.GetHeight());
        std::vector<Point> figures;
        std::vector<image::Color> s_rgb;
        GetRandomValues(figures, s_rgb, image);
        for (size_t y = 0; y < image.GetHeight(); ++y) {
            for (size_t x = 0; x < image.GetWidth(); ++x) {
                size_t dmin = (x - figures[0].x) * (x - figures[0].x) + (y - figures[0].y) * (y - figures[0].y);
                size_t j = 0;
                for (size_t i = 1; i < cnt_of_figures_; i++) {
                    size_t d = (x - figures[i].x) * (x - figures[i].x) + (y - figures[i].y) * (y - figures[i].y);
                    if (d < dmin) {
                        dmin = d;
                        j = i;
                    }
                }
                result_image(y, x) = s_rgb[j];
            }
        }
        return result_image;
    }

private:
    void GetRandomValues(std::vector<Point>& figures, std::vector<image::Color>& s_rgb,
                         const image::Image& image) const {
        for (int i = 0; i < cnt_of_figures_; i++) {
            size_t x = std::rand() % image.GetWidth();
            size_t y = std::rand() % image.GetHeight();
            figures.push_back(Point(x, y));
            s_rgb.push_back(image(y, x));
        }
    }

private:
    size_t cnt_of_figures_;
};

REGISTER_FILTER("crystall", CICrystallize::Factory)

}  // namespace image_processor::filters
