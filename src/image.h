#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <string>

namespace Image {

// Paths
const std::string fileName{"/mandelbrot.png"};
const std::string fileDirectory{"../images"};  // up one directory from build

// Defaults
// const int bitDepth = 32;  // image bit depth

// TEMPORARY: Create Red Image
// void CreateImage(int width, int height);

// void plot(window<int>& scr,
//           std::vector<int>& colors,
//           int iter_max,
//           const char* fname,
//           bool smooth_color);

}  // namespace Image

#endif