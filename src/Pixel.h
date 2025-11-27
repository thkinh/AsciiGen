#pragma once
#include <cmath>
#include <cstddef>

class Pixel
{
public:
    Pixel() {}
    ~Pixel() {}
    Pixel(size_t red, size_t green, size_t blue);
    const float getLuminance() const;

private:
    size_t m_red = 0;
    size_t m_green = 0;
    size_t m_blue = 0;
    float m_luminance = 0;
};
