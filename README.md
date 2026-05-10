# AsciiGen: Convert images to ascii characters

## Preview
<img width="1306" height="1006" alt="image" src="https://github.com/user-attachments/assets/7a624d0f-ef55-47f3-8d85-f3522b928444" />
 
## Usage

### Basic Conversion

Convert a PNG image into ASCII art:

```bash
./build/ascii_gen <image_path>
```

Example:

```bash
./build/ascii_gen ~/Pictures/cat.png
```

### Resize the Output

You can reduce the output dimensions by providing horizontal and vertical compression values:

```bash
./build/ascii_gen <image_path> <width_compression> <height_compression>
```

- `width_compression` — reduces the image width by the specified factor
- `height_compression` — reduces the image height by the specified factor

Higher values produce smaller ASCII output.

Example:

```bash
./build/ascii_gen ./assets/original-apple.png 8 16
```

This command:
- reduces the image width by a factor of 8
- reduces the image height by a factor of 16

---

## Build Instructions

Clone the repository and generate the executable with CMake:

```bash
git clone https://github.com/thkinh/AsciiGen.git
cd AsciiGen
mkdir build
cd build
cmake ..
```

The executable will be generated as:

```bash
./build/ascii_gen
```

---

## Notes

- Currently, only PNG images are supported.
- Compression values affect the output resolution directly.
- Terminal font and window size can affect the appearance of the generated ASCII art.

## Unimplemented Features

- Support for additional image formats
- Specify output dimensions directly instead of compression factors
- Improved character interval mapping for better grayscale representation
