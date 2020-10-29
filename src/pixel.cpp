#include "pixel.h"
#include <stdexcept>

// constructors
Pixel::Pixel(int x, int y) : x_(x), y_(y) {
  image_ = nullptr;
  fractal_ = nullptr;
  // x coordinate real; y coordinate imaginary
  cartesianCoords_ = std::complex<double>((double)x, (double)y);
}

Pixel::Pixel(int x, int y, Window<int>* image, Window<double>* fractal)
    : x_(x), y_(y), image_(image), fractal_(fractal) {
  cartesianCoords_ = std::complex<double>((double)x, (double)y);
  if (image == nullptr) {
    throw std::invalid_argument("image is null pointer");
  }
  if (fractal == nullptr) {
    throw std::invalid_argument("fractal is null pointer");
  }
}

// getters

std::complex<double> Pixel::cartesianCoords() const {
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
  Pixel::red(Mandelbrot::BernsteinRed(tValue));
  Pixel::green(Mandelbrot::BernsteinGreen(tValue));
  Pixel::blue(Mandelbrot::BernsteinBlue(tValue));
}

// set data handles (not owned)
void Pixel::image(Window<int>* image) {
  image_ = image;
}
void Pixel::fractal(Window<double>* fractal) {
  fractal_ = fractal;
}

// compute complex domain of pixel coordinates
std::complex<double> Pixel::GetComplexCoords() {
  return Mandelbrot::ComplexFromCartesian(image_, fractal_, cartesianCoords_);
}