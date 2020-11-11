#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include "display.h"
#include "mandelbrot.h"
#include "pixel_queue.h"
#include "window.h"

int main() {
  // shared pointer to image
  std::shared_ptr<Window<int>> image =
      std::make_shared<Window<int>>(500, 500);  // 1200 800

  // shared pointer to fractal
  std::shared_ptr<Window<double>> fractal =
      std::make_shared<Window<double>>(-2.2, 1.2, -1.7,
                                       1.7);  // subset to search for points

  std::chrono::high_resolution_clock::time_point startTime =
      std::chrono::high_resolution_clock::now();

  // initialize SDL2 display
  Display display(image,
                  fractal);  // display shares ownership of image and fractal

  // render initial mandelbrot set
  display.renderMandelbrotSet();

  //   std::cout << "Render initial Mandelbrot Set"
  //             << "\n";
  std::chrono::high_resolution_clock::time_point endTime =
      std::chrono::high_resolution_clock::now();

  double cycleDuration =
      std::chrono::duration<double, std::ratio<1, 1>>(endTime - startTime)
          .count();

  std::cout << "execution time: " << cycleDuration << std::endl;

  display.initializeEventQueue();

  return 0;
}
