#include "PixelBuffer.h"
#include "Pixel.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>

PixelBuffer::PixelBuffer(size_t width, size_t height):
    m_width(width), m_height(height)
{
    m_data.resize(width * height);
}


size_t PixelBuffer::height() const
{
    return m_height;
}

size_t PixelBuffer::width() const 
{
    return m_width;
}

void PixelBuffer::resize(size_t width, size_t height)
{
    m_width = width;
    m_height = height;
    m_data.resize(width * height);
}

const Pixel& PixelBuffer::at(size_t x, size_t y) const
{
    if(x > m_width || y > m_height)
    {
        throw std::runtime_error("Out of bound");
    }
    return m_data[x*y];
}
   
void PixelBuffer::setPixel(size_t x, size_t y,const Pixel& p) 
{
    m_data[x*y] = p;
}

const void PixelBuffer::preview(size_t head) const
{
    float maxLum = 0.0f;
    float minLum = 10000.0f;

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            const Pixel& px = m_data[y * m_width + x];
            float lum = px.getLuminance();

            if (lum > maxLum) maxLum = lum;
            if (lum < minLum) minLum = lum;
        }
    }
    std::cout << "MaxLum/MinLum: " << maxLum << "/" << minLum << "\n";
}

