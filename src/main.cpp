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
  /*
  // shared pointer to image
  std::shared_ptr<Window<int>> image =
      std::make_shared<Window<int>>(500, 500);  // 1200 800

  // shared pointer to fractal
  std::shared_ptr<Window<double>> fractal =
      std::make_shared<Window<double>>(-2.2, 1.2, -1.7,
                                       1.7);  // subset to search for points

  // initialize SDL2 display
  Display display(image,
                  fractal);  // display shares ownership of image and fractal

  // render initial mandelbrot set
  display.RenderMandelbrotSet();

  std::cout << "Render initial Mandelbrot Set"
            << "\n";

  display.InitializeEventQueue();

  // display.ClearDisplay(); // NOT USED
  */
  return 0;
}
