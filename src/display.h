#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include <memory>
#include "pixel_queue.h"

class Display {
 public:
  // constructor
  Display(std::shared_ptr<Window<int>> image,
          std::shared_ptr<Window<double>> fractal);

  // destructor
  ~Display();

  // TO DO: rule of five

  // proprietary methods
  PixelQueue ConstructPixelQueue();   // construct and return queue of pixels
  void RenderDefaultMandelbrotset();  // render default mandelbrot set
  void InitializeEventQueue();        // handle SDL events
  void ClearDisplay();                // set display background to white
  void RecenterFractal(const int x,
                       const int y);  // recenter subset to search for points
 private:
  int width_;
  int height_;

  // data handles (owned)
  std::shared_ptr<Window<int>> image_;  // TO DO: image_ should not be owned.
  std::shared_ptr<Window<double>> fractal_;

  // pointers to SDL objects
  SDL_Window* win_{nullptr};
  SDL_Renderer* ren_{nullptr};
};

#endif