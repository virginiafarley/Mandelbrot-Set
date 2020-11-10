#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <complex>
#include "window.h"

namespace Mandelbrot {

const int MAX_ITERATIONS{
    200};  // maximum number of iterations to determine if
           // sequence bounded in absolute value for given point

const double MOVE_PERCENTAGE{.10};  // default amount to move display

const double ZOOM_MULTIPLIER{
    .5};  // default multiplier for zooming into / out o f display

// return Mandelbrot function f_c(z) = z^2 + c
std::complex<double> mandelbrotFunction(std::complex<double>& z,
                                        const std::complex<double>& c);

// convert Cartesian coordinates to complex coordinates
// source: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
std::complex<double> complexFromCartesian(Window<int>* image,
                                          Window<double>* fractal,
                                          std::complex<double>& coordinates);

// return number of iterations adjusted to [0, 1] interval
// source: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
double bernsteinTValue(const int& nIterations);

// return Bernstein t value from escape time algorithm
double tValueFromEscapeTime(const std::complex<double>& c);

// determine RGB pixel colors from Bernstein polynomials
// source: https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
int bernsteinRed(const double& tValue);
int bernsteinBlue(const double& tValue);
int bernsteinGreen(const double& tValue);

}  // namespace Mandelbrot

#endif