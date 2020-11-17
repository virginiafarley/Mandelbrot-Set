#include "mandelbrot.h"

// Mandelbrot function
void Mandelbrot::mandelbrotFunction(std::complex<double>& z,
                                    const std::complex<double>& c) {
  z = std::pow(z, 2) + c;
}

// convert Cartesian coordinates to Complex coordinates
// source: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
std::complex<double> Mandelbrot::complexFromCartesian(
    Window<int>* image,
    Window<double>* fractal,
    const std::complex<double> coordinates) {
  double real =
      coordinates.real() / image->width() * fractal->width() + fractal->x_min();

  double imaginary = coordinates.imag() / image->height() * fractal->height() +
                     fractal->y_min();

  return std::complex<double>(real, imaginary);
}

// adjust number of iterations to [0, 1] interval
// source: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
double Mandelbrot::bernsteinTValue(const int nIterations) {
  return (double)nIterations /
         (double)Mandelbrot::MAX_ITERATIONS;  // [0, 1] interval
}

// return Bernstein t value from escape time algorithm
double Mandelbrot::tValueFromEscapeTime(const std::complex<double>& c) {
  std::complex<double> z{0};
  int nIterations{0};
  while (true) {
    // if abs(z) > 2 or MAX_ITERATIONS reached, sequence will escape to infinity
    if (std::abs(z) > 2 || nIterations >= Mandelbrot::MAX_ITERATIONS) {
      break;
    }
    Mandelbrot::mandelbrotFunction(z, c);
    nIterations++;
  }
  return Mandelbrot::bernsteinTValue(
      nIterations);  // use t value to color pixels
}

// determine RGB pixel colors from Bernstein polynomials
// source: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
int Mandelbrot::bernsteinRed(const double& tValue) {
  return 9 * (1.0 - tValue) * std::pow(tValue, 3.0) * 255;
}

int Mandelbrot::bernsteinBlue(const double& tValue) {
  return 8.5 * std::pow(1.0 - tValue, 3.0) * tValue * 255;
}
int Mandelbrot::bernsteinGreen(const double& tValue) {
  return 15 * std::pow(1.0 - tValue, 2.0) * std::pow(tValue, 2.0) * 255;
}