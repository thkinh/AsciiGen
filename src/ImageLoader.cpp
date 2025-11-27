#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb/stb_image.h"
#include "ImageLoader.h"
#include "PixelBuffer.h"
#include <string>


bool BMPImageLoader::load(const std::string& path, PixelBuffer& pixelBuffer)
{
    return true;
}

bool PNGImageLoader::load(const std::string& path, PixelBuffer& outBuffer)
{
    int w, h, channels;

    // Load with original channels (stb_image will detect 3 or 4 automatically)
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 0);

    if (!data) return false;

    outBuffer.resize(w, h);

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int idx = y * w * channels + x * channels;

            unsigned char r = data[idx + 0];
            unsigned char g = data[idx + 1];
            unsigned char b = data[idx + 2];
            if (x < 5 && y < 5) {
                printf("Pixel %d,%d = %d %d %d alpha=%d\n", x, y, r, g, b,
                        (channels==4 ? data[idx+3] : -1));
            }


            // If image has alpha channel, blend against white background
            if (channels == 4)
            {
                float alpha = data[idx + 3] / 255.f;
                r = static_cast<unsigned char>(r * alpha + 255 * (1 - alpha));
                g = static_cast<unsigned char>(g * alpha + 255 * (1 - alpha));
                b = static_cast<unsigned char>(b * alpha + 255 * (1 - alpha));
            }

            Pixel px(r, g, b);
            outBuffer.setPixel(x, y, px);
        }
    }
    stbi_image_free(data);
    return true;
}

