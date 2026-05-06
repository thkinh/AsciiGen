#pragma once
#include <algorithm>
#include <cstddef>
#include <map>
#include <memory>
#include <vector>
#include "Pixel.h"
#include "AsciiCanvas.h"
#include "PixelBuffer.h"
#include <string>

class AsciiConverter
{
public:
    AsciiConverter() {}
    AsciiConverter(size_t interval);

    const char convert(const Pixel& p) const;
    const char convert(float lum) const;
    const char convert(size_t lum) const;
    const char convertBlock(const PixelBuffer& buffer, size_t x, size_t y, size_t blockWidth, size_t blockHeight) const;

    bool convertWholeCanvas(AsciiCanvas& canvas, const PixelBuffer& buffer);
    bool convertWholeCanvasByBlock(AsciiCanvas& canvas, const PixelBuffer& buffer, size_t blockWidth, size_t blockHeight);
    const std::map<size_t, char> getMap() const;

    bool registerAscii(size_t brightress, char asciiChar);
    bool registerAsciiList(const std::string& charList);

private:
    size_t m_minLum;
    size_t m_maxLum;
    size_t m_interval = 100;
    std::map<size_t, char> m_asciiMap;
};
