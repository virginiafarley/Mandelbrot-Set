#include "display.h"
#include <iostream>
#include <stdexcept>

Display::Display(std::shared_ptr<Window<int>> image,
                 std::shared_ptr<Window<double>> fractal)
    : width_(image->width()),
      height_(image->height()),
      image_(image),
      fractal_(fractal),
      pixels_(image.get(), fractal.get()) {
  // launch worker threads that construct pixel
  pixels_.waitForLaunch();

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
    throw std::runtime_error("SDL window creation failed");
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

  // std::cout << "Initialize display. Width: " << image->width() << "\t"
  //           << " Height: " << image->height() << "\n";
}

Display::~Display() {
  SDL_DestroyWindow(win_);
  SDL_DestroyRenderer(ren_);
  SDL_Quit();
}

// render default mandelbrot set
void Display::renderMandelbrotSet() {
  // wait until all threads have completed execution
  pixels_.waitForCompletion();

  SDL_Event e;
  SDL_PollEvent(&e);

  for (int y = 0; y < image_->height(); y++) {   // iterate rows (y-axis)
    for (int x = 0; x < image_->width(); x++) {  // iterate columns (x - axis)

      Pixel& pixel = pixels_(x, y);

      // SDL_ALPHA_OPAQUE: alpha value of 255
      SDL_SetRenderDrawColor(ren_, pixel.red(), pixel.green(), pixel.blue(),
                             SDL_ALPHA_OPAQUE);

      SDL_RenderDrawPoint(ren_, pixel.x(), pixel.y());
    }
  }

  // update display since last call
  SDL_RenderPresent(ren_);
}

// update rendering
void Display::updateRendering() {
  pixels_.waitForLaunch();  // synchronize threads
  renderMandelbrotSet();    // render new display
}

// handle SDL events
void Display::initializeEventQueue() {
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
          // recenter display to mouse button event location
          moveDisplay(e.button);
          break;
        case SDL_KEYDOWN:
          switch (e.key.keysym.sym) {
            // arrow keys
            case SDLK_UP:
              moveDisplay(Direction::Up);
              break;
            case SDLK_DOWN:
              moveDisplay(Direction::Down);
              break;
            case SDLK_RIGHT:
              moveDisplay(Direction::Right);
              break;
            case SDLK_LEFT:
              moveDisplay(Direction::Left);
              break;
            // WASD keys
            case SDLK_w:
              moveDisplay(Direction::Up);
              break;
            case SDLK_s:
              moveDisplay(Direction::Down);
              break;
            case SDLK_a:
              moveDisplay(Direction::Right);
              break;
            case SDLK_d:
              moveDisplay(Direction::Left);
              break;
            // zoom in/out
            case SDLK_EQUALS:
              zoomIntoDisplay(ZoomDirection::In);
              break;
            case SDLK_MINUS:
              zoomIntoDisplay(ZoomDirection::Out);
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
// void Display::clearDisplay() {
//   std::cout << "Clear display."
//             << "\n";
//   SDL_SetRenderDrawColor(ren_, 255, 255, 255, SDL_ALPHA_OPAQUE);
//   SDL_RenderClear(ren_);
//   SDL_RenderPresent(ren_);
// }

// recenter subset to search for points
void Display::recenterFractal(const int x, const int y) {
  double pcntRight = (double)(x - width_ / 2) / (double)width_;
  double pcntUp = (double)(y - height_ / 2) / (double)height_;

  fractal_->moveAlongAxes(pcntRight, pcntUp);
}

void Display::recenterFractal(Direction direction) {
  double pcntUp;  // note that sdl2 inverts y-axis (i.e. y coordinate increases
                  // as you move down)
  double pcntRight;

  switch (direction) {
    case Direction::Up:
      pcntUp = -Mandelbrot::MOVE_PERCENTAGE;
      pcntRight = .0;
      break;
    case Direction::Down:
      pcntUp = Mandelbrot::MOVE_PERCENTAGE;
      pcntRight = .0;
      break;
    case Direction::Right:
      pcntUp = .0;
      pcntRight = Mandelbrot::MOVE_PERCENTAGE;
      break;
    case Direction::Left:
      pcntUp = .0;
      pcntRight = -Mandelbrot::MOVE_PERCENTAGE;
      break;
    default:
      break;
  }
  fractal_->moveAlongAxes(pcntRight, pcntUp);
}

// move display when mouse event occurs
void Display::moveDisplay(SDL_MouseButtonEvent button) {
  recenterFractal(button.x,
                  button.y);  // set new fractal position

  updateRendering();  // update display
}

// move display when arrow key pressed
void Display::moveDisplay(Direction direction) {
  recenterFractal(direction);  // set new fractal position

  updateRendering();  // update display
}

// zoom into / out of display when +/- key pressed
void Display::zoomIntoDisplay(ZoomDirection direction) {
  switch (direction) {
    case ZoomDirection::In:
      fractal_->zoomIntoWindow(Mandelbrot::ZOOM_MULTIPLIER);
      break;
    case ZoomDirection::Out:
      fractal_->zoomIntoWindow(1 / Mandelbrot::ZOOM_MULTIPLIER);
    default:
      break;
  }
  updateRendering();
}

// return total number of pixels to display
int Display::pixelCount() {
  return width_ * height_;
}