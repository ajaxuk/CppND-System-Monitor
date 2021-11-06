#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <unordered_map>
#include <vector>

class Processor {
 public:
  float Utilization();

  // DONE: See src/processor.cpp
  // DONE: Declare any necessary private members

 private:
  long prev_active_jiffies_{};
  long prev_idle_jiffies_{};
};

#endif