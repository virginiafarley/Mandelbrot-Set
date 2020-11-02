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

  ~Display();                                   // destructor
  Display(const Display&) = delete;             // copy constructor
  Display& operator=(const Display&) = delete;  // copy assignment operator
  Display(Display&&) = delete;                  // move constructor
  Display& operator=(Display&&) = delete;       // move assignment operator

  // proprietary methods
  PixelQueue ConstructPixelQueue();  // construct and return queue of pixels
  void RenderMandelbrotSet();        // render default mandelbrot set
  void InitializeEventQueue();       // handle SDL events
  void ClearDisplay();               // set display background to white

  void RecenterFractal(const int x,
                       const int y);  // recenter subset to search for points
  void MoveDisplayToMouseEvent(
      SDL_MouseButtonEvent button);  // move display when mouse event occurs

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