#pragma once

namespace image_processor::image {

struct Color {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    void ToNormalValues();
};

Color operator+(const Color& a, const Color& b);
Color operator-(const Color& a, const Color& b);
Color operator*(const Color& a, const Color& b);
Color operator*(const Color& c, float a);
Color operator*(float a, const Color& c);
Color operator/(const Color& c, float a);

}  // namespace image_processor::image
