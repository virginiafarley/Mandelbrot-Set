#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include "pixel_queue.h"

class Display {
 public:
  // constructor
  Display(int width, int height);

  // destructor
  ~Display();

  // TO DO: rule of five

  // proprietary methods

  void RenderMandelbrotSet(PixelQueue pixels);  // render mandelbrot set
  void InitializeEventQueue();                  // handle SDL events
  void ClearDisplay();  // set display background to white

 private:
  int width_;
  int height_;

  // pointers to SDL objects
  SDL_Window* win_{nullptr};
  SDL_Renderer* ren_{nullptr};
};

#endif