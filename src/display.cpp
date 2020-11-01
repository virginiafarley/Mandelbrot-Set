#include "display.h"
#include <iostream>
#include <stdexcept>

Display::Display(std::shared_ptr<Window<int>> image,
                 std::shared_ptr<Window<double>> fractal)
    : width_(image->width()),
      height_(image->height()),
      image_(image),
      fractal_(fractal) {
  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    throw std::runtime_error("SDL initialization failed");
  }

  // Create window positioned at center of screen
  win_ = SDL_CreateWindow("Mandelbrot Set", SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED, image->width(),
                          image->height(), SDL_WINDOW_SHOWN);
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
  std::cout << "Initialize display. Width: " << image->width() << "\t"
            << " Height: " << image->height() << "\n";
}

Display::~Display() {
  SDL_DestroyWindow(win_);
  SDL_DestroyRenderer(ren_);
  SDL_Quit();
}

// construct and return queue of pixels
PixelQueue Display::ConstructPixelQueue() {
  PixelQueue pixels(image_.get(), fractal_.get());
  return pixels;  // not copied due to RVO
}

// render default mandelbrot set
void Display::RenderDefaultMandelbrotset() {
  std::cout << "Render default Mandelbrot Set."
            << "\n";
  PixelQueue pixels = ConstructPixelQueue();

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
      switch (e.type) {
        case SDL_QUIT:
          quit = true;
        case SDL_MOUSEBUTTONDOWN:
          if (e.button.button != SDL_BUTTON_LEFT) {
            break;
          }
          // update fractal when mouse event occurs
          RecenterFractal(e.button.x, e.button.y);
          break;
        case SDL_KEYDOWN:
          switch (e.key.keysym.sym) {
            case SDLK_UP:
              std::cout << "zoom in\n";
              break;
            case SDLK_DOWN:
              std::cout << "zoom out\n";
              break;
          }
          break;
        default:
          break;
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

// recenter subset to search for points
void Display::RecenterFractal(const int x, const int y) {
  std::cout << "new x center:\t" << x << " new y center:\t" << y << "\n";

  double moveRightPcnt = (double)(x - width_ / 2) / (double)width_;
  double moveUpPcnt = (double)(height_ / 2 - y) / (double)height_;
  std::cout << "move right percent: " << moveRightPcnt << "\n";
  std::cout << "move up percent: " << moveUpPcnt << "\n";

  // std::cout << "units of image: " << moveRightPcnt * (double)width_ << "\n";
  // std::cout << "units of image: " << moveUpPcnt * (double)height_ << "\n";

  // std::cout << fractal_->width() << "\n";
  std::cout << "move fractal right units: "
            << moveRightPcnt * fractal_->width();
  std::cout << "move fractal up units: " << moveUpPcnt * fractal_->height();
}
