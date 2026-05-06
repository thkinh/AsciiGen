#include <cstddef>
#include <iostream>
#include "PixelBuffer.h"
#include "ImageLoader.h"
#include "AsciiConverter.h"
#include "AsciiCanvas.h"

int main() {
    //Create the buffer for storing pixels
    PixelBuffer buf = PixelBuffer();
    PNGImageLoader loader = PNGImageLoader();

    if(!loader.load("../assets/original-apple.png", buf))
    {
        std::cout << "Failed\n";
        return 1;
    }
    buf.preview(50);

    size_t interval = 10;
    AsciiConverter converter(interval);

    //Register ascii chars
    std::string charList = "@WMBQGNRD$S&%E8gmHwA#K96CUZPXdqbp5023Vae4FhokYsynTcJ[]z7L?xv{}1f>j<t()=I|+lr!i^/\\\"*~;_' :, -`.";
    converter.registerAsciiList(charList);

    //Draw the buffer to the canvas
    size_t blockWidth  = 4;
    size_t blockHeight = 10;
    AsciiCanvas canvas = AsciiCanvas(buf.width()/blockWidth, buf.height()/blockHeight);
    if(converter.convertWholeCanvasByBlock(canvas, buf, blockWidth, blockHeight))
    {
        canvas.render(false);
    }
    return 0;
}
