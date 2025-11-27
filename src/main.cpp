#include <cstddef>
#include <iostream>
#include "PixelBuffer.h"
#include "ImageLoader.h"
#include "AsciiConverter.h"
#include "AsciiCanvas.h"

int main() {
    size_t width = 10;
    size_t height = 10;
    PixelBuffer buf = PixelBuffer(width, height);
    
    PNGImageLoader loader = PNGImageLoader();

    if(!loader.load("../assets/1.png", buf))
    {
        std::cout << "Failed\n";
        return 1;
    }
    width = buf.width();
    height = buf.height();


    buf.preview(50);

    size_t interval = 255;
    AsciiConverter converter(interval);

    const char charList[] =
        "@WMBQGNRD$S&%E8gmHwA#K96CUZPXdqbp5023Vae4FhokYsynTcJ[]z7L?xv{}1f>j<t()=I|+lr!i^/\\\"*~;_' :, -`.";
    const size_t asciiCount = sizeof(charList) - 1; // without null

    for (size_t i = 0; i < interval; i++)
    {
        char c = charList[i % asciiCount];

        converter.registerAscii(static_cast<size_t>(i), c);
    }

    AsciiCanvas canvas = AsciiCanvas(width, height);
    canvas.clear();
    for(size_t i = 0; i < width; i++)
    {
        for(size_t j = 0; j < height; j++)
        {
            canvas.setChar(i, j, converter.convert(buf.at(i, j))); 
        }
    }
    
    canvas.render();



    return 0;
}
