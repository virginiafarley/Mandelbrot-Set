#include "pixel_queue.h"
#include <stdexcept>

PixelQueue::PixelQueue(Window<int>* image, Window<double>* fractal)
    : image_(image), fractal_(fractal) {
  if (image == nullptr) {
    throw std::invalid_argument("image is null pointer");
  }
  if (fractal == nullptr) {
    throw std::invalid_argument("fractal is null pointer");
  }
  pushAll();  // construct and add all pixels to queue
}

PixelQueue::~PixelQueue() {
  // wait for all threads to complete
  std::for_each(futures_.begin(), futures_.end(),
                [](std::future<void>& ftr) { ftr.wait(); });

  // destroy all elements to improve space overhead
  futures_.clear();
}

// set data handles (not owned)
void PixelQueue::image(Window<int>* image) {
  image_ = image;
}
void PixelQueue::fractal(Window<double>* fractal) {
  fractal_ = fractal;
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
    Pixel pixel(j, rowNumber);

    // calculate complex domain of pixel coordinates
    std::complex<double> complexCoords = Mandelbrot::complexFromCartesian(
        image_, fractal_, pixel.cartesianCoords());

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