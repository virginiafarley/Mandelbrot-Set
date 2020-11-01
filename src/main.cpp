
// #include <SDL.h>
#include <iostream>
#include <memory>
// #include <opencv2/opencv.hpp>
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

  // initialize SDL2 display
  Display display(image,
                  fractal);  // display shares ownership of image and fractal

  // render initial mandelbrot set
  display.RenderMandelbrotSet();

  display.InitializeEventQueue();

  // use mouse to move around
  // when you click, x and y coordinates becom the center
  // for example, center starts at 250, 250
  // when you click 0, 250: x2 - x1 = -250.  xmin xmax + the new delta
  // change new center to complex number

  // display needs ownership of pixel queue saved as member variable
  // pixel queue needs new constructors / modifiers to modify pixels

  // display.ClearDisplay(); // TO DO: figure out later.
  return 0;
}
