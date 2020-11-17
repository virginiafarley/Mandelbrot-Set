#include "pixel_vector.h"
#include <iostream>

// constructor
PixelVector::PixelVector(Window<int>* image, Window<double>* fractal)
    : image_(image), fractal_(fractal) {
  if (image == nullptr) {
    throw std::invalid_argument("image is null pointer");
  }
  if (fractal == nullptr) {
    throw std::invalid_argument("fractal is null pointer");
  }

  // initialize vector of pixels
  for (int i = 0; i < image->height(); i++) {  // iterate rows (y-axis)
    std::vector<Pixel> row;
    for (int j = 0; j < image->width(); j++) {  // iterate columns (x-axis)
      Pixel pixel(j, i);

      row.emplace_back(std::move(pixel));
    }
    pixels_.emplace_back(std::move(row));
  }

  size_t threadCount =
      std::thread::hardware_concurrency();  // number of threads

  workersDone =
      std::make_unique<Barrier>(threadCount + 1);  // include main thread
  workersReady =
      std::make_unique<Barrier>(threadCount + 1);  // include main thread

  for (size_t i = 0; i < threadCount; i++) {
    threads_.emplace_back(
        std::thread(&PixelVector::runWorkerThreads, this, i, threadCount));
  }
}

// destructor
PixelVector::~PixelVector() {
  terminateWorkers.store(true);

  // properly exit when threads waiting for conditional variable
  workersReady->wait();

  // wait for all threads to complete
  std::for_each(threads_.begin(), threads_.end(),
                [](std::thread& t) { t.join(); });
}

// color pixels in thread
void PixelVector::runWorkerThreads(int threadID, size_t threadCount) {
  while (!terminateWorkers.load()) {  // FIGURE THIS OUT LATER TOO
    // wait 1 ms between cycles
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    workersReady->wait();

    if (terminateWorkers.load()) {
      return;
    }

    for (int y = threadID; y < image_->height();
         y += threadCount) {                       // iterate rows (y-axis)
      for (int x = 0; x < image_->width(); x++) {  // iterate columns (x - axis)

        // calculate complex domain of pixel coordinates
        std::complex<double> complexCoords = Mandelbrot::complexFromCartesian(
            image_, fractal_, std::complex<double>((double)x, (double)y));

        // compute Bernstein t value using escape time algoirthm
        double tValue = Mandelbrot::tValueFromEscapeTime(complexCoords);

        // color pixel from Bernstein polynomials
        pixels_[y][x].color(tValue);
      }
    }

    workersDone->wait();
  }
}

// return when entire vector has been constructed
void PixelVector::waitForCompletion() {
  // wait for all threads to complete iteration
  workersDone->wait();
}

// return when all threads ready to launch
void PixelVector::waitForLaunch() {
  // wait for all threads to complete iteration
  workersReady->wait();
}
// access pixel by location
Pixel& PixelVector::operator()(int row, int col) {
  return pixels_[row][col];
}