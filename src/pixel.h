#ifndef PIXEL_H
#define PIXEL_H

#include "mandelbrot.h"

class Pixel {
 public:
  // constructors
  Pixel(int x, int y);
  Pixel(int x, int y, Window<int>* image, Window<double>* fractal);

  // getters
  std::complex<double> cartesianCoords() const;  // return cartesian coordinates
  int x() const;                                 // get x position
  int y() const;                                 // get y position

  int red() const;
  int blue() const;
  int green() const;

  // setters
  void red(int red);
  void blue(int blue);
  void green(int green);
  void color(const double& tValue);  // set rgb colors from Bernstein tvalue

  // set data handles (not owned)
  void image(Window<int>* image);
  void fractal(Window<double>* fractal);

  // proprietary functions

  // compute complex domain of pixel coordinates
  std::complex<double> GetComplexCoords();

 private:
  // rgb colors
  int red_{0};
  int blue_{0};
  int green_{0};

  // cartesian coordinates
  int x_;
  int y_;
  std::complex<double> cartesianCoords_;

  // data handles (not owned)
  Window<int>* image_;       // raw pointer to image
  Window<double>* fractal_;  // raw pointer to fractal
};

#endif