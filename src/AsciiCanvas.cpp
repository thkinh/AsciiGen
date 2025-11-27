#include "AsciiCanvas.h"
#include <iostream>

AsciiCanvas::AsciiCanvas(size_t width, size_t height)
    : m_width(width), m_height(height), m_data(width * height, ' ')
{
}

void AsciiCanvas::setChar(size_t x, size_t y, char c)
{
    if (x >= m_width || y >= m_height) return;  // silently ignore OOB
    m_data[y * m_width + x] = c;
}

char AsciiCanvas::getChar(size_t x, size_t y) const
{
    if (x >= m_width || y >= m_height) return ' ';
    return m_data[y * m_width + x];
}

void AsciiCanvas::clear(char fill)
{
    std::fill(m_data.begin(), m_data.end(), fill);
}

void AsciiCanvas::render(bool trailSpace = false) const
{
    if(trailSpace)
    {
        for (size_t y = 0; y < m_height; ++y) {
            for (size_t x = 0; x < m_width; ++x) {
                char c = m_data[y * m_width + x];
                std::cout << c << ' ';   // add a space to widen
            }
            std::cout << '\n';
        }
        return;
    }
    // Print row-by-row
    for (size_t y = 0; y < m_height; ++y) {
        const char* row = &m_data[y * m_width];
        std::cout.write(row, m_width);
        std::cout << '\n';
    }
}
