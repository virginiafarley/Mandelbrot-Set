#ifndef PIXEL_QUEUE_H
#define PIXEL_QUEUE_H

#include <queue>
#include "pixel.h"

class PixelQueue {
 public:
  // constructor
  PixelQueue(Window<int>* image, Window<double>* fractal);

  // typical behavior methods
  Pixel popFront();  // remove and return first pixel in queue

  void pushBack(Pixel&& pixel);  // add pixel to back of queue

  size_t size();  // queue size
  bool empty();   // return true when queue empty

 private:
  std::queue<Pixel> pixels_;

  // data handles (not owned)
  Window<int>* image_;       // raw pointer to image
  Window<double>* fractal_;  // raw pointer to fractal
};

#endif