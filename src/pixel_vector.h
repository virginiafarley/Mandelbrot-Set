#ifndef PIXEL_VECTOR_H
#define PIXEL_VECTOR_H

#include <atomic>
#include <future>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include "barrier.h"
#include "pixel.h"

class PixelVector {
 public:
  //  constructor
  PixelVector(Window<int>* image, Window<double>* fractal);

  // destructor
  ~PixelVector();

  PixelVector(const PixelVector&) = delete;  // copy constructor
  PixelVector& operator=(const PixelVector&) =
      delete;                                      // copy assignment operator
  PixelVector(PixelVector&&) = delete;             // move constructor
  PixelVector& operator=(PixelVector&&) = delete;  // move assignment operator

  // typical behavior methods
  void runWorkerThreads(int threadID,
                        size_t threadCount);  // color pixels in thread
  void waitForCompletion();  // return when entire vector has been constructed
  void waitForLaunch();      // return when all threads ready to launch
  Pixel& operator()(int row,
                    int col);  // access pixel by location (read only)

 private:
  std::vector<std::vector<Pixel>> pixels_;
  std::vector<std::thread> threads_;

  std::atomic<bool> terminateWorkers{false};  // terminate worker threads
  std::unique_ptr<Barrier> workersDone;       // thread synchronization barrier
  std::unique_ptr<Barrier> workersReady;      // thread synchronization barrier

  std::mutex mutex_;              // protects shared resource pixels_
  std::condition_variable cond_;  // signaling mechanism

  // data handles (not owned)
  Window<int>* image_;       // raw pointer to image
  Window<double>* fractal_;  // raw pointer to fractal
};

#endif