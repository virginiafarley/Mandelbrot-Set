#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <complex>
#include "window.h"

namespace Mandelbrot {

const int maxIterations{
    100};  // maximum number of iterations to determine if
           // sequence bounded in absolute value for given point

// return Mandelbrot function f_c(z) = z^2 + c
std::complex<double> MandelbrotFunction(std::complex<double>& z,
                                        const std::complex<double>& c);

// convert Cartesian coordinates to complex coordinates
// source: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
std::complex<double> ComplexFromCartesian(Window<int>* image,
                                          Window<double>* fractal,
                                          std::complex<double>& coordinates);

// return number of iterations adjusted to [0, 1] interval
// source: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
double BernsteinTValue(const int& nIterations);

// return Bernstein t value from escape time algorithm
double TValueFromEscapeTime(const std::complex<double>& c);

// determine RGB pixel colors from Bernstein polynomials
// source: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
int BernsteinRed(const double& tValue);
int BernsteinBlue(const double& tValue);
int BernsteinGreen(const double& tValue);

}  // namespace Mandelbrot

#endif