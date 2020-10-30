# Mandelbrot Set

This is a rendering of the Mandelbrot set.  Note that it is more efficient to calculating the Mandelbrot with the GPU (e.g. OpenGL shaders) instead of the CPU.

Zooming in on the Mandelbrot set illustrates its infinitely complex pattern.  This boundary is a fractal curve, meaning that regardless of the level of magnification, the curve retains the same general pattern of irregularity.

For more information, please refer to [Wolfram MathWorld](https://mathworld.wolfram.com/MandelbrotSet.html).

This project is adapted from the tutorial [Solarian Programmer](https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/).


[TwinklebearDev](https://www.willusher.io/pages/sdl2/) SDL2 tutorial.

SDL2 Keyboard information: [Handling the Keyboard](https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html)

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* OpenCV
  * in progress
  * https://github.com/opencv/opencv for information
* SDL2
  * TBD

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./mandelbrot_set`.