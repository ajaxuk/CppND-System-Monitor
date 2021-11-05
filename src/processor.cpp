#include "processor.h"

#include <iostream>
#include <string>
#include <vector>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization

using namespace LinuxParser;

float Processor::Utilization() {
  long total_delta{0};
  long idle_delta{0};

  long active_jiffies = LinuxParser::ActiveJiffies();
  long idle_jiffies = LinuxParser::IdleJiffies();

  total_delta =
      (active_jiffies + idle_jiffies) - (prev_active_jiffies_ + prev_idle_jiffies_);
  idle_delta = idle_jiffies - prev_idle_jiffies_;

  // store current as previous for next round of calculations
  prev_active_jiffies_ = active_jiffies;
  prev_idle_jiffies_ = idle_jiffies;

  return (float)(total_delta - idle_delta) / total_delta;
}