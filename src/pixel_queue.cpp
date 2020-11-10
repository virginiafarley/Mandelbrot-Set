#include "pixel_queue.h"

PixelQueue::PixelQueue(Window<int>* image, Window<double>* fractal)
    : image_(image), fractal_(fractal) {
  pushAll();  // construct and add all pixels to queue
}

PixelQueue::~PixelQueue() {
  // wait for all threads to complete
  std::for_each(futures_.begin(), futures_.end(),
                [](std::future<void>& ftr) { ftr.wait(); });

  // destroy all elements to improve space overhead
  futures_.clear();
}

// add all pixels to queue
void PixelQueue::pushAll() {
  for (int i = 0; i < image_->height(); i++) {  // iterate rows (y-axis)
    futures_.emplace_back(
        // launch thread for each row
        std::async(std::launch::any, &PixelQueue::constructPixelRow, this, i));
  }
}

// create row of pixels
void PixelQueue::constructPixelRow(int rowNumber) {
  for (int j = 0; j < image_->width(); j++) {  // iterate columns (x-axis)
    // pixel instances hold non-owning reference to image and fractal
    Pixel pixel(j, rowNumber, image_, fractal_);

    // calculate complex representation of pixel coordinates
    std::complex<double> complexCoords = pixel.GetComplexCoords();

    // compute Bernstein t value using escape time algoirthm
    double tValue = Mandelbrot::tValueFromEscapeTime(complexCoords);

    // color pixel from Bernstein polynomials
    pixel.color(tValue);

    // send pixel to back of queue
    queue_.send(std::move(pixel));
  }
}
// return when entire queue has been constructed
void PixelQueue::waitForCompletion() {
  // wait for all threads to complete
  std::for_each(futures_.begin(), futures_.end(),
                [](std::future<void>& ftr) { ftr.wait(); });

  // destroy all elements to improve space overhead
  futures_.clear();
}

// remove and return first pixel in queue
Pixel PixelQueue::popFront() {
  Pixel pixel = queue_.receive();

  return pixel;  // not copied due to RVO
}

// queue size
size_t PixelQueue::size() {
  return queue_.size();
}

bool PixelQueue::empty() {
  return queue_.empty();
}