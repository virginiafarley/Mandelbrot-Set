#include "barrier.h"

Barrier::Barrier(size_t threadCount)
    : threadCount_(threadCount), counter(threadCount), generation(0) {}

void Barrier::wait() {
  std::unique_lock<std::mutex> uLock(mutex_);  // fence mechanism
  auto lastGeneration = generation;

  if (!--counter) {
    generation++;
    counter = threadCount_;
    cond_.notify_all();
  }

  else {
    cond_.wait(uLock,
               [this, lastGeneration] { return lastGeneration != generation; });
  }
}