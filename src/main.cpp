
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "image.h"
#include "pixel.h"

int main() {
  // shared pointer to image
  std::shared_ptr<Window<int>> image =
      std::make_shared<Window<int>>(1200, 1200);

  // shared pointer to fractal
  std::shared_ptr<Window<double>> fractal =
      std::make_shared<Window<double>>(-2.2, 1.2, -1.7,
                                       1.7);  // subset to search for points

  for (int i = 1000; i < image->height(); i++) {   // iterate rows (y-axis)
    for (int j = 1000; j < image->width(); j++) {  // iterate columns (x-axis)
      // pixel instances hold non-owning reference to image and fractal
      Pixel pixel(j, i, image.get(), fractal.get());

      // calculate complex representation of pixel coordinates
      std::complex<double> complexCoords = pixel.GetComplexCoords();

      // compute Bernstein t value using escape time algoirthm
      double tValue = Mandelbrot::TValueFromEscapeTime(complexCoords);

      // color pixel from Bernstein polynomials
      pixel.color(tValue);

      // std::cout << "red: " << pixel.red() << "\t"
      //           << "green: " << pixel.green() << "\t"
      //           << "blue: " << pixel.blue() << "\n";
    }
  }
  // Image::CreateImage(image->width(), image->height());

  // fileStream.open("images/logs.txt");
  // if (fileStream.fail()) {
  //   // file could not be opened
  // }

  return 0;
}