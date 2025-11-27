#pragma once
#include <vector>

class AsciiCanvas {
public:
    AsciiCanvas(size_t width, size_t height);

    void setChar(size_t x, size_t y, char c);
    char getChar(size_t x, size_t y) const;

    void clear(char fill = ' ');
    void render() const;  // print whole canvas at once

private:
    size_t m_width;
    size_t m_height;
    std::vector<char> m_data;
};

