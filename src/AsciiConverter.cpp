#include "AsciiConverter.h"
#include "AsciiCanvas.h"
#include "Pixel.h"
#include "PixelBuffer.h"
#include <cstddef>
#include <iostream>
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

bool AsciiConverter::registerAsciiList(const std::string& charList)
{
    if (charList.empty()) {
        return false;
    }

    bool succeed = false;
    const size_t asciiCount = charList.length();

    for (size_t i = 0; i < m_interval; i++)
    {
        char c = charList[i % asciiCount];
        succeed = registerAscii(static_cast<size_t>(i), c);
    }
    return succeed;
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

const char AsciiConverter::convert(float lum, size_t custom_interval) const
{
    size_t brightness = static_cast<size_t>(
            (lum / 255.0f) * (custom_interval - 1)
            );

    brightness = std::clamp(brightness, (size_t)0, custom_interval - 1);

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

bool AsciiConverter::convertWholeCanvas(AsciiCanvas& canvas, const PixelBuffer& buffer)
{
    size_t width = buffer.width();
    size_t height = buffer.height();
    canvas.clear();
    for(size_t i = 0; i < width; i++)
    {
        for(size_t j = 0; j < height; j++)
        {
            canvas.setChar(i, j, convert(buffer.at(i, j))); 
        }
    }
    return true;
}

bool AsciiConverter::convertWholeCanvasByBlock(AsciiCanvas& canvas, const PixelBuffer& buffer, size_t blockWidth, size_t blockHeight) 
{
    size_t width = buffer.width();
    size_t height = buffer.height();
    size_t x = 0;
    size_t y = 0;
    canvas.clear();

    for(size_t i = 0; i <= width-blockWidth; i+=blockWidth) {
        y = 0;
        for(size_t j = 0; j <= height-blockHeight; j+=blockHeight) {
            canvas.setChar(x, y, convertBlock(buffer, i, j, blockWidth, blockHeight));
            y++;
        }
        x++;
    }
    return true;
}

const char AsciiConverter::convertBlock(const PixelBuffer& buffer, size_t x, size_t y, size_t blockWidth, size_t blockHeight) const {
    float compressedLum = 0;
    for(size_t i = x; i < x + blockWidth; i++) {
        for(size_t j = y; j < y + blockHeight; j++) {
            compressedLum += buffer.at(i, j).getLuminance()/4;
        }
    }
    compressedLum /= (blockWidth * blockHeight);
    return convert(compressedLum);
}
