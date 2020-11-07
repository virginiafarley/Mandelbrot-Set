#include "pixel_queue.h"

PixelQueue::PixelQueue(Window<int>* image, Window<double>* fractal)
    : image_(image), fractal_(fractal) {
  for (int i = 0; i < image->height(); i++) {  // iterate rows (y-axis)
    futures_.emplace_back(
        // launch thread for each row
        std::async(std::launch::any, &PixelQueue::constructPixelRow, this, i));
  }
}

PixelQueue::~PixelQueue() {
  // wait for all threads to complete
  std::for_each(futures_.begin(), futures_.end(),
                [](std::future<void>& ftr) { ftr.wait(); });
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
    pixels_.send(std::move(pixel));
  }
}

// PixelQueue::PixelQueue(Window<int>* image, Window<double>* fractal)
//     : image_(image), fractal_(fractal) {
//   for (int i = 0; i < image->height(); i++) {   // iterate rows (y-axis)
//     for (int j = 0; j < image->width(); j++) {  // iterate columns (x-axis)

//       // pixel instances hold non-owning reference to image and fractal
//       Pixel pixel(j, i, image, fractal);

//       // calculate complex representation of pixel coordinates
//       std::complex<double> complexCoords = pixel.GetComplexCoords();

//       // compute Bernstein t value using escape time algoirthm
//       double tValue = Mandelbrot::tValueFromEscapeTime(complexCoords);

//       // color pixel from Bernstein polynomials
//       pixel.color(tValue);

//       // move pixel to back of queue (move constructor)
//       pixels_.emplace(std::move(pixel));
//     }
//   }
//   // std::cout << "Create queue of pixels. Size: "
//   //           << "\t" << size() << "\n";
// }

// // remove and return first pixel in queue
// Pixel PixelQueue::popFront() {
//   Pixel pixel = std::move(pixels_.front());
//   pixels_.pop();

//   return pixel;  // not copied due to RVO
// }

// // add pixel to back of queue
// void PixelQueue::pushBack(Pixel&& pixel) {
//   pixels_.emplace(std::move(pixel));
// }

// size_t PixelQueue::size() {
//   return pixels_.size();
// };

// bool PixelQueue::empty() {
//   return pixels_.empty();
// }