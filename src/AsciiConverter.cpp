#include "AsciiConverter.h"
#include "Pixel.h"
#include <cstddef>
#include <map>
#include <stdexcept>
#include <string>

AsciiConverter::AsciiConverter(size_t interval):
    m_interval(interval)
{}

bool AsciiConverter::registerAscii(size_t brightness, char asciiChar)
{
    if(brightness > m_interval || brightness < 0)
    {
        std::string brightnessString = std::to_string(brightness);
        std::string errorString = "brightness value must be within [0, interval]: \nCurrent brightness: ";
        errorString += brightnessString;
        throw std::runtime_error(errorString) ;
        return false;
    }

    m_asciiMap[brightness] = asciiChar;
    return true;
}

const char AsciiConverter::convert(const Pixel& p) const
{
    float lum = std::clamp(p.getLuminance(), 0.0f, 255.0f);

    size_t brightness = static_cast<size_t>(
        (lum / 255.0f) * (m_interval - 1)
    );

    brightness = std::clamp(brightness, (size_t)0, m_interval - 1);

    return m_asciiMap.at(brightness);
}

const char AsciiConverter::convert(float lum) const
{
    size_t brightness = static_cast<size_t>(
        (lum / 255.0f) * (m_interval - 1)
    );

    brightness = std::clamp(brightness, (size_t)0, m_interval - 1);

    return m_asciiMap.at(brightness);
}


const char AsciiConverter::convert(size_t brightness) const 
{
    return m_asciiMap.at(brightness);
}

const std::map<size_t, char> AsciiConverter::getMap() const 
{
    return m_asciiMap;
}
