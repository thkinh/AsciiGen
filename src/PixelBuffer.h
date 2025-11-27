#pragma once
#include <cstddef>
#include <vector>
#include "Pixel.h"

class PixelBuffer {
public:
    PixelBuffer(size_t width, size_t height);

    //Pixel& at(size_t x, size_t y);
    const Pixel& at(size_t x, size_t y) const;

    size_t width() const;
    size_t height() const;

    void resize(size_t width, size_t height);
    void setPixel(size_t x, size_t y, const Pixel& p);

    const void preview(size_t head) const;

private:
    size_t m_width;
    size_t m_height;
    std::vector<Pixel> m_data;
};
