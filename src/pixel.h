#ifndef PIXEL_H
#define PIXEL_H

#include "mandelbrot.h"

class Pixel {
 public:
  // constructors
  Pixel();
  Pixel(int x, int y);

  // getters
  const std::complex<double>& cartesianCoords()
      const;      // return cartesian coordinates
  int x() const;  // get x position
  int y() const;  // get y position

  int red() const;
  int blue() const;
  int green() const;

  // setters
  void red(int red);
  void blue(int blue);
  void green(int green);
  void color(const double& tValue);  // set rgb colors from Bernstein tvalue

 private:
  // rgb colors
  int red_{0};
  int blue_{0};
  int green_{0};

  // cartesian coordinates
  int x_;
  int y_;
  const std::complex<double>
      cartesianCoords_;  // x coordinate real; y coordinate imaginary
};

#endif