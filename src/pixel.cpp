#include "pixel.h"
#include <stdexcept>

// constructors
Pixel::Pixel() {}

Pixel::Pixel(int x, int y)
    : x_(x),
      y_(y),
      cartesianCoords_(std::complex<double>((double)x, (double)y)) {}

// getters

const std::complex<double>& Pixel::cartesianCoords() const {
  return cartesianCoords_;
}

int Pixel::x() const {
  return x_;
}

int Pixel::y() const {
  return y_;
}

int Pixel::red() const {
  return red_;
}

int Pixel::blue() const {
  return blue_;
}

int Pixel::green() const {
  return green_;
}

// setters
void Pixel::red(int red) {
  if (red < 0 || red > 255) {
    throw std::invalid_argument("rgb integer value must be between 0 and 255");
  }
  red_ = red;
}

void Pixel::blue(int blue) {
  if (blue < 0 || blue > 255) {
    throw std::invalid_argument("rgb integer value must be between 0 and 255");
  }
  blue_ = blue;
}

void Pixel::green(int green) {
  if (green < 0 || green > 255) {
    throw std::invalid_argument("rgb integer value must be between 0 and 255");
  }
  green_ = green;
}

// set rgb colors from Bernstein tvalue
void Pixel::color(const double& tValue) {
  Pixel::red(Mandelbrot::bernsteinRed(tValue));
  Pixel::green(Mandelbrot::bernsteinGreen(tValue));
  Pixel::blue(Mandelbrot::bernsteinBlue(tValue));
}
