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

  long activejiffies = LinuxParser::ActiveJiffies();
  long idlejiffies = LinuxParser::IdleJiffies();

  total_delta =
      (activejiffies + idlejiffies) - (prev_active_jiffies_ + prev_idle_jiffies_);
  idle_delta = idlejiffies - prev_idle_jiffies_;

  // store current as previous for next round of calculations
  prev_active_jiffies_ = activejiffies;
  prev_idle_jiffies_ = idlejiffies;

  return (float)(total_delta - idle_delta) / total_delta;
}