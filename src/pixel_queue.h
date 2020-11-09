#ifndef PIXEL_QUEUE_H
#define PIXEL_QUEUE_H

#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include "pixel.h"

template <class T>
class MessageQueue {
 public:
  T receive() {
    // perform queue modification under the lock
    std::unique_lock<std::mutex> uLock(mutex_);
    cond_.wait(uLock, [this] {
      return !messages_.empty();
    });  // pass unique lock to condition variable

    // remove first element from queue
    T msg = std::move(messages_.front());
    messages_.pop();

    return msg;  // will not be copied due to return value optimization (RVO) in
                 // C++
  }

  void send(T&& msg) {
    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(mutex_);

    // add element to back of queue
    messages_.emplace(std::move(msg));
    cond_.notify_one();  // notify client after pushing new element
  }

 private:
  std::mutex mutex_;              // protects shared resource pixels_
  std::condition_variable cond_;  // signaling mechanism
  std::queue<T> messages_;
};

class PixelQueue {
 public:
  // constructor
  PixelQueue(Window<int>* image, Window<double>* fractal);

  // destructor
  ~PixelQueue();

  PixelQueue(const PixelQueue&) = delete;  // copy constructor
  PixelQueue& operator=(const PixelQueue&) =
      delete;                                    // copy assignment operator
  PixelQueue(PixelQueue&&) = delete;             // move constructor
  PixelQueue& operator=(PixelQueue&&) = delete;  // move assignment operator

  // typical behavior methods

  void constructPixelRow(int rowNumber);  // create row of pixels
  Pixel popFront();          // remove and return first pixel in queue
  void waitForCompletion();  // return when entire queue has been constructed

  // TO DO : figure out how to receive messages and sent them to display

  // void pushBack(Pixel&& pixel);  // add pixel to back of queue

  // size_t size();  // queue size
  // bool empty();   // return true when queue empty

 private:
  MessageQueue<Pixel> queue_;  // queue of pixels
  std::vector<std::future<void>> futures_;

  // data handles (not owned)
  Window<int>* image_;       // raw pointer to image
  Window<double>* fractal_;  // raw pointer to fractal
};

#endif