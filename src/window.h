#ifndef WINDOW_H
#define WINDOW_H

#include <stdexcept>

template <typename T>
class Window {
 public:
  // constructors
  Window(T width, T height)
      : x_min_(0),
        x_max_(width),
        y_min_(0),
        y_max_(height),
        width_(width),
        height_(height) {
    if (width <= 0) {
      throw std::invalid_argument("window width must be positive");
    }
    if (height <= 0) {
      throw std::invalid_argument("window height must be positive");
    }
  }

  Window(T x_min, T x_max, T y_min, T y_max)
      : x_min_(x_min),
        x_max_(x_max),
        y_min_(y_min),
        y_max_(y_max),
        width_(x_max - x_min),
        height_(y_max - y_min) {
    if (x_max - x_min <= 0) {
      throw std::invalid_argument("window width must be positive");
    }
    if (y_max - y_min <= 0) {
      throw std::invalid_argument("window height must be positive");
    }
  }

  // getters
  T x_min() const { return x_min_; }
  T x_max() const { return x_max_; }
  T y_min() const { return y_min_; }
  T y_max() const { return y_max_; }

  T width() const { return width_; }
  T height() const { return height_; }

  // setters
  void x_min(T x_min) {
    x_min_ = x_min;
    width_ = x_max_ - x_min;
    if (width_ <= 0) {
      throw std::invalid_argument("window width must be positive");
    }
  }
  void x_max(T x_max) {
    x_max_ = x_max;
    width_ = x_max - x_min_;
    if (width_ <= 0) {
      throw std::invalid_argument("window width must be positive");
    }
  }
  void y_min(T y_min) {
    y_min_ = y_min;
    height_ = y_max_ - y_min;
    if (height_ <= 0) {
      throw std::invalid_argument("window height must be positive");
    }
  }
  void y_max(T y_max) {
    y_max_ = y_max;
    height_ = y_max - y_min_;
    if (height_ <= 0) {
      throw std::invalid_argument("window height must be positive");
    }
  }

  // move window right on x-axis and update x_min and x_max
  void moveXAxisRight(double pcntRight) {
    double unitsRight = pcntRight * width_;  // units to move right
    x_min_ += unitsRight;
    x_max_ += unitsRight;
  }

  // move window up on y-axis and update y_min and y_max
  void moveYAxisUp(double pcntUp) {
    double unitsUp = pcntUp * height_;  // units to move up
    y_min_ += unitsUp;
    y_max_ += unitsUp;
  }

  // move window right on x-axis and up on y-axis
  void moveAlongAxes(double pcntRight, double pcntUp) {
    double unitsUp = pcntUp * height_;  // units to move up
    y_min_ += unitsUp;
    y_max_ += unitsUp;

    double unitsRight = pcntRight * width_;  // units to move right
    x_min_ += unitsRight;
    x_max_ += unitsRight;
  }

  void width(T width) {
    if (width <= 0) {
      throw std::invalid_argument("window width must be positive");
    }
    width_ = width;
    x_min_ = 0;
    x_max_ = width;
  }

  void height(T height) {
    if (height <= 0) {
      throw std::invalid_argument("window height must be positive");
    }
    height_ = height;
    y_min_ = 0;
    y_max_ = height;
  }

  // typical behavior methods

  T area() const { return width_ * height_; }  // window area

 private:
  T x_min_;
  T x_max_;
  T y_min_;
  T y_max_;

  T width_;
  T height_;
};

#endif