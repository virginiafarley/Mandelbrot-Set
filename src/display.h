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

  void renderMandelbrotSet();   // render default mandelbrot set
  void updateRendering();       // update rendering
  void initializeEventQueue();  // handle SDL events
  void clearDisplay();          // set display background to white
  void recenterFractal(const int x,
                       const int y);  // recenter subset to search for points
  void moveDisplayToMouseEvent(
      SDL_MouseButtonEvent button);  // move display when mouse event occurs

  int pixelCount();  // return total number of pixels to display

 private:
  int width_;
  int height_;

  // data handles (owned)

  PixelQueue pixels_;  // object that holds pixels to display

  std::shared_ptr<Window<int>> image_;  // TO DO: image_ should not be owned.
  std::shared_ptr<Window<double>> fractal_;

  // pointers to SDL objects
  SDL_Window* win_{nullptr};
  SDL_Renderer* ren_{nullptr};
};

#endif