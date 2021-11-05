#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

class Processor {
 public:
  float Utilization();


  // TODO: See src/processor.cpp
  // TODO: Declare any necessary private members

 private:



  long prev_active_jiffies_{};
  long prev_idle_jiffies_{};
};

#endif