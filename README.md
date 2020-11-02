# Mandelbrot Set

This is a rendering of the Mandelbrot set.  This project is adapted from the tutorial [Solarian Programmer](https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/).

Zooming in on the Mandelbrot set illustrates its infinitely complex pattern.  This boundary is a fractal curve, meaning that regardless of the level of magnification, the curve retains the same general pattern of irregularity.  For more information, please refer to [Wolfram MathWorld](https://mathworld.wolfram.com/MandelbrotSet.html) or [Wikipedia](https://en.wikipedia.org/wiki/Mandelbrot_set).

To learn more about how SDL2 is used in this project, please refer to the SDL2 tutorial [TwinklebearDev](https://www.willusher.io/pages/sdl2/) and the SDL2 library keyboard documentation [Handling the Keyboard](https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html).

## Dependencies for Running Locally
* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL2 >= 2.0.12
  * All OSecs: [click here for installation instructions](https://wiki.libsdl.org/Installation)
  * Mac: can also install with brew: `brew install sdl2` and use pkg-config to set compile flags and library options: `pkg-config --cflags --libs sld2`.
  * Linux and Windows: for more information, please refer to this tutorial: (https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./mandelbrot_set`.