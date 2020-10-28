#include "mandelbrot.h"

// Mandelbrot function
std::complex<double> Mandelbrot::MandelbrotFunction(
    std::complex<double>& z,
    const std::complex<double>& c) {
  return std::pow(z, 2) + c;
}

// convert Cartesian coordinates to Complex coordinates
// source: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
std::complex<double> Mandelbrot::ComplexFromCartesian(
    Window<int>* image,
    Window<double>* fractal,
    std::complex<double>& coordinates) {
  double real =
      coordinates.real() / image->width() * fractal->width() + fractal->x_min();

  double imaginary = coordinates.imag() / image->height() * fractal->height() +
                     fractal->y_min();

  return std::complex<double>(real, imaginary);
}

// adjust number of iterations to [0, 1] interval
// source: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
double Mandelbrot::BernsteinTValue(const int& nIterations) {
  return (double)nIterations /
         (double)Mandelbrot::maxIterations;  // [0, 1] interval
}

// return Bernstein t value from escape time algorithm
double Mandelbrot::TValueFromEscapeTime(const std::complex<double>& c) {
  std::complex<double> z{0};
  int nIterations{0};
  while (true) {
    // if abs(z) > 2 or maxIterations reached, sequence will escape to infinity
    if (std::abs(z) > 2 || nIterations >= Mandelbrot::maxIterations) {
      break;
    }
    z = Mandelbrot::MandelbrotFunction(z, c);
    nIterations++;
  }
  return Mandelbrot::BernsteinTValue(
      nIterations);  // use t value to color pixels
}

// determine RGB pixel colors from Bernstein polynomials
// source: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
int Mandelbrot::BernsteinRed(const double& tValue) {
  return 9 * (1.0 - tValue) * std::pow(tValue, 3.0) * 255;
}

int Mandelbrot::BernsteinBlue(const double& tValue) {
  return 8.5 * std::pow(1.0 - tValue, 3.0) * tValue * 255;
}
int Mandelbrot::BernsteinGreen(const double& tValue) {
  return 15 * std::pow(1.0 - tValue, 2.0) * std::pow(tValue, 2.0) * 255;
}