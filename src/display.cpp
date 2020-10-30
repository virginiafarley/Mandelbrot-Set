#include "display.h"
#include <iostream>
#include <stdexcept>

Display::Display(int width, int height) : width_(width), height_(height) {
  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("SDL initialization failed");
  }

  // Create window positioned at center of screen
  win_ =
      SDL_CreateWindow("Mandelbrot Set", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  if (win_ == nullptr) {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
  }

  // Create a renderer that will draw to the window
  // -1 loads video driver that supports accelerated and presentsync flags
  // SDL_RENDERER_ACCELERATED: use hardware accelerated rendering (GPU)
  // SDL_RENDERER_PRESENTVSYNC: renderer's present function (update screen)
  // synchronized with the monitor's refresh rate
  ren_ = SDL_CreateRenderer(
      win_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren_ == nullptr) {
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("SDL renderer failed");
  }
  std::cout << "Initialize display. Width: " << width << "\t"
            << " Height: " << height << "\n";
}

Display::~Display() {
  SDL_DestroyWindow(win_);
  SDL_DestroyRenderer(ren_);
  SDL_Quit();
}

// render mandelbrot set
void Display::RenderMandelbrotSet(PixelQueue pixels) {
  std::cout << "Render Mandelbrot Set."
            << "\n";
  SDL_Event e;
  SDL_PollEvent(&e);

  while (!pixels.empty()) {
    Pixel pixel = pixels.popFront();

    // SDL_ALPHA_OPAQUE: alpha value of 255
    SDL_SetRenderDrawColor(ren_, pixel.red(), pixel.green(), pixel.blue(),
                           SDL_ALPHA_OPAQUE);

    SDL_RenderDrawPoint(ren_, pixel.x(), pixel.y());
  }

  // // update display since last call
  SDL_RenderPresent(ren_);
}

// handle SDL events
void Display::InitializeEventQueue() {
  std::cout << "Initialize event queue."
            << "\n";
  bool quit = false;
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }
}

// set display background to white
void Display::ClearDisplay() {
  std::cout << "Clear Display"
            << "\n";
  SDL_SetRenderDrawColor(ren_, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(ren_);
  SDL_RenderPresent(ren_);
}
