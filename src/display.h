#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include "pixel_queue.h"

/*
namespace Image {

// Paths - to do; make static constexpr
const std::string fileName{"/mandelbrot.png"};
const std::string fileDirectory{"../images"};  // up one directory from build

*/

class Display {
 public:
  // constructor
  Display(int width, int height);

  // destructor
  ~Display();

  // to do: rule of five

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

/*




// A sleepy rendering loop, wait for 3 seconds and render and present the
// screen each time
for (int i = 0; i < 3; ++i) {
  // First clear the renderer
  SDL_RenderClear(ren);

  // Update the screen
  SDL_RenderPresent(ren);
  // Take a quick break after all that hard work
  SDL_Delay(1000);


    // pause display
  SDL_Delay(1000);
}
}

*/

#endif