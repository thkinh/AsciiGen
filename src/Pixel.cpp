#include "Pixel.h"

Pixel::Pixel(size_t red, size_t green, size_t blue):
    m_red(red), m_green(green), m_blue(blue)
{
    m_red   = m_red   > 255 ? 255 : m_red;
    m_green = m_green > 255 ? 255 : m_green;
    m_blue  = m_blue  > 255 ? 255 : m_blue;

    m_red   = m_red   < 0 ? 0 : m_red;
    m_green = m_green < 0 ? 0 : m_green;
    m_blue  = m_blue  < 0 ? 0 : m_blue;

    m_luminance = 0.2126*m_red + 0.7152*m_green + 0.0722*m_blue;
}

const float Pixel::getLuminance() const
{
    return m_luminance;
}
