#include <cstddef>
#include <iostream>
#include "PixelBuffer.h"
#include "ImageLoader.h"
#include "AsciiConverter.h"
#include "AsciiCanvas.h"

int main(int argc, char** argv) {
    //Create the buffer for storing pixels
    PixelBuffer buf = PixelBuffer();
    PNGImageLoader loader = PNGImageLoader();

    const char* file_name;

    if (argc > 1) {
        file_name = argv[1];
    } else {
        file_name = "../assets/original-apple.png";
    }

    if(!loader.load(file_name, buf))
    {
        std::cout << "File does not exist, or cannot convert the image\n";
        return 1;
    }
    buf.preview(50);

    size_t interval = 90;
    AsciiConverter converter(interval);

    //Register ascii chars
    //std::string charList = "@WMBQGNRD$S&%E8gmHwA#K96CUZPXdqbp5023Vae4FhokYsynTcJ[]z7L?xv{}1f>j<t()=I|+lr!i^/\\\"*~;_' :, -`.";
    std::string charList = "@WMe4Fho -`.";
    converter.registerAsciiList(charList);

    //Draw the buffer to the canvas
    size_t blockWidth  = 4;
    size_t blockHeight = 8;
    AsciiCanvas canvas = AsciiCanvas(buf.width()/blockWidth, buf.height()/blockHeight);
    if(converter.convertWholeCanvasByBlock(canvas, buf, blockWidth, blockHeight))
    {
        canvas.render(false);
    }
    return 0;
}
