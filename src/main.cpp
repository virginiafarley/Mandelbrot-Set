
// #include <SDL.h>
#include <iostream>
#include <memory>
// #include <opencv2/opencv.hpp>
#include <string>
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

  PixelQueue pixels(image.get(), fractal.get());

  // initialize SDL2 display
  Display display(image->width(), image->height());
  // display.ClearDisplay(); figure this part out

  while (!pixels.empty()) {
    Pixel pixel = pixels.popFront();
  }

  // pixel.red(255);
  // pixel.blue(0);
  // pixel.green(255);
  // display.RenderPoint(pixel);

  // for (int i = 0; i < 10; i++) {    // iterate rows (y-axis)
  //   for (int j = 0; j < 10; j++) {  // iterate columns (x-axis)
  //     Pixel pixel(j, i);
  //     pixel.red(255);
  //     pixel.green(10);
  //     pixel.blue(255);
  //     // std::cout << pixel.x() << "\t" << pixel.y() << "\n";
  //     display.RenderPoint(pixel);
  //   }
  // }
  // display.InitializeEventQueue();
  return 0;
}
