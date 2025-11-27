#pragma once
#include <algorithm>
#include <cstddef>
#include <map>
#include <memory>
#include <vector>
#include "Pixel.h"

class AsciiConverter
{
public:
    AsciiConverter() {}
    AsciiConverter(size_t interval);

    const char convert(const Pixel& p) const;
    const char convert(float lum) const;
    const char convert(size_t lum) const;
    const std::map<size_t, char> getMap() const;

    bool registerAscii(size_t brightress, char asciiChar);

private:
    size_t m_minLum;
    size_t m_maxLum;
    size_t m_interval = 100;
    std::map<size_t, char> m_asciiMap;
};
