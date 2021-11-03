#include "processor.h"

#include <iostream>
#include <string>
#include <vector>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization

using namespace LinuxParser;

// Convert string to long and store in Private variable
void Processor::Utilization(std::vector<std::string> &utilization) {
  for (int i = kUser_; i <= kGuestNice_; i++) {
    utilization_[i] = std::stol(utilization[i]);
  }
}

float Processor::Utilization() {
  long total_delta;
  long idle_delta;
  long prev_activejiffies = utilization_[kUser_] + utilization_[kNice_] +
                            utilization_[kSystem_] + utilization_[kIRQ_] +
                            utilization_[kSoftIRQ_] + utilization_[kSteal_];

  long prev_idlejiffies = utilization_[kIdle_] + utilization_[kIOwait_];

  std::vector<std::string> stats = LinuxParser::CpuUtilization();
  Utilization(stats);
  long activejiffies = utilization_[kUser_] + utilization_[kNice_] +
                       utilization_[kSystem_] + utilization_[kIRQ_] +
                       utilization_[kSoftIRQ_] + utilization_[kSteal_];

  long idlejiffies = utilization_[kIdle_] + utilization_[kIOwait_];

  total_delta =
      (activejiffies + idlejiffies) - (prev_activejiffies + prev_idlejiffies);
  idle_delta = idlejiffies - prev_idlejiffies;

  return (float)(total_delta - idle_delta) / total_delta;
}