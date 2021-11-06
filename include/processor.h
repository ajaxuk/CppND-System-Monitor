#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>
#include <unordered_map>


class Processor {
 public:
  float Utilization();
  std::unordered_map<int,int> prev_proc_jiffy{};  //<pid,jiffy>

  // TODO: See src/processor.cpp
  // TODO: Declare any necessary private members

 private:

  
  long prev_active_jiffies_{};
  long prev_idle_jiffies_{};
};

#endif