#ifndef BARRIER_H
#define BARRIER_H

#include <condition_variable>
#include <mutex>

class Barrier {
 public:
  // constructor
  Barrier(size_t threadCount);

  // fence mechanism
  void wait();

 private:
  std::mutex mutex_;              // protects shared resources
  std::condition_variable cond_;  // signaling mechanism

  size_t threadCount_;  // count down threads required to release barrier
  size_t counter;
  size_t generation;
};

#endif