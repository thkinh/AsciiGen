#include <cstddef>
#include <cstdlib>
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
    size_t blockWidth = 0;
    size_t blockHeight = 0;
    if (argc > 1) {
        file_name = argv[1];
    } else {
        file_name = "../assets/original-apple.png";
    }

    if(argc > 2) {
        blockWidth  = atoi(argv[2]);
        blockHeight = atoi(argv[3]);
    } else {
        blockWidth = 4;
        blockHeight = 8;
    }

    if(blockWidth == 0 || blockHeight == 0) {
        std::cout << "wrong block size\n";
        return 1;
    }

    if(!loader.load(file_name, buf))
    {
        std::cout << "File does not exist, or cannot convert the image\n";
        return 1;
    }
    buf.preview(50);

    size_t interval = 30;
    AsciiConverter converter(interval);

    //Register ascii chars
    //std::string charList = "@WMBQGNRD$S&%E8gmHwA#K96CUZPXdqbp5023Vae4FhokYsynTcJ[]z7L?xv{}1f>j<t()=I|+lr!i^/\\\"*~;_' :, -`.";
    std::string charList = "@ ";
    converter.registerAsciiList(charList);

    //Draw the buffer to the canvas
    AsciiCanvas canvas = AsciiCanvas(buf.width()/blockWidth, buf.height()/blockHeight);
    std::cout << "Final w/h " << buf.width()/blockWidth << " " << buf.height()/blockHeight << "\n";
    if(converter.convertWholeCanvasByBlock(canvas, buf, blockWidth, blockHeight))
    {
        canvas.render(false);
    }
    return 0;
}
