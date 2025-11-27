#include <cstddef>
#include <iostream>
#include "PixelBuffer.h"
#include "ImageLoader.h"
#include "AsciiConverter.h"
#include "AsciiCanvas.h"

int main() {
    size_t width = 0;
    size_t height = 0;
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

    size_t interval = 95;
    AsciiConverter converter(interval);

    const char charList[] =
        "@WMBQGNRD$S&%E8gmHwA#K96CUZPXdqbp5023Vae4FhokYsynTcJ[]z7L?xv{}1f>j<t()=I|+lr!i^/\\\"*~;_' :, -`.";
    const size_t asciiCount = sizeof(charList) - 1; // without null
    std::cout << "\nChar count: " << asciiCount << "\n";

    for (size_t i = 0; i < interval; i++)
    {
        char c = charList[i % asciiCount];
        converter.registerAscii(static_cast<size_t>(i), c);
    }

    AsciiCanvas canvas = AsciiCanvas(width, height);
    if(converter.convertWholeCanvas(canvas, buf))
    {
        canvas.render(false);
    }
    return 0;
}
