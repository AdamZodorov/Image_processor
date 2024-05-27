#include "color.h"
#include <algorithm>
#include <initializer_list>

namespace image_processor::image {

Color operator+(const Color& a, const Color& b) {
    return Color{
        .r = a.r + b.r,
        .g = a.g + b.g,
        .b = a.b + b.b,
    };
}

Color operator-(const Color& a, const Color& b) {
    return Color{
        .r = a.r - b.r,
        .g = a.g - b.g,
        .b = a.b - b.b,
    };
}

Color operator*(const Color& a, const Color& b) {
    return Color{
        .r = a.r * b.r,
        .g = a.g * b.g,
        .b = a.b * b.b,
    };
}

Color operator*(const Color& c, float a) {
    return c * Color{a, a, a};
}

Color operator*(float a, const Color& c) {
    return c * a;
}

Color operator/(const Color& c, float a) {
    return c * (1.0f / a);
}

void Color::ToNormalValues() {
    for (float* x : std::initializer_list<float*>{&r, &g, &b}) {
        *x = std::clamp(*x, 0.0f, 1.0f);
    }
}

}  // namespace image_processor::image
