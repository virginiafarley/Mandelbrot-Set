
// #include <SDL.h>
#include <iostream>
#include <memory>
// #include <opencv2/opencv.hpp>
#include <string>
#include <thread>
#include <vector>
#include "display.h"
#include "pixel_queue.h"

int main() {
  // shared pointer to image
  std::shared_ptr<Window<int>> image =
      std::make_shared<Window<int>>(500, 500);  // 1200 800

  // shared pointer to fractal
  std::shared_ptr<Window<double>> fractal =
      std::make_shared<Window<double>>(-2.2, 1.2, -1.7,
                                       1.7);  // subset to search for points

  // initialize SDL2 display
  Display display(image->width(), image->height());

  // construct queue of pixels
  PixelQueue pixels(image.get(), fractal.get());

  // display takes ownership of pixel queue
  // TO DO: perhaps do not maintain ownership when zoom in or recenter?
  display.RenderMandelbrotSet(std::move(pixels));

  display.InitializeEventQueue();

  // display.ClearDisplay(); // TO DO: figure out later.
  return 0;
}
