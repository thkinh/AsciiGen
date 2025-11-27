#pragma once
#include "PixelBuffer.h"
#include <string>

class IImageLoader {
public:
    virtual ~IImageLoader() = default;

    virtual bool load(const std::string& filepath, PixelBuffer& pixelBuffer) = 0;
};

class BMPImageLoader : public IImageLoader {
public:
   bool load(const std::string& filepath, PixelBuffer& pixelBuffer) override;
};

class PNGImageLoader : public IImageLoader {
public:
    bool load(const std::string& filepath, PixelBuffer& pixelBuffer) override;
};

