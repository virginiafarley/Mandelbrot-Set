#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include "display.h"
#include "mandelbrot.h"
#include "pixel_vector.h"
#include "window.h"

int main() {
  // shared pointer to image
  std::shared_ptr<Window<int>> image = std::make_shared<Window<int>>(500, 500);

  // shared pointer to fractal
  std::shared_ptr<Window<double>> fractal =
      std::make_shared<Window<double>>(-2.2, 1.2, -1.7,
                                       1.7);  // subset to search for points

  // initialize SDL2 display
  Display display(image,
                  fractal);  // display shares ownership of image and fractal

  std::chrono::high_resolution_clock::time_point startTime =
      std::chrono::high_resolution_clock::now();

  // render initial mandelbrot set
  display.renderMandelbrotSet();

  std::cout << "Render initial Mandelbrot Set"
            << "\n";
  std::chrono::high_resolution_clock::time_point endTime =
      std::chrono::high_resolution_clock::now();

  double cycleDuration =
      std::chrono::duration<double, std::ratio<1, 1000>>(endTime - startTime)
          .count();

  std::cout << "Execution time: " << cycleDuration << " ms " << std::endl;

  display.initializeEventQueue();

  return 0;
}
