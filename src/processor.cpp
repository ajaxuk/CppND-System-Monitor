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
  long total_delta{0};
  long idle_delta{0};
  long prev_activejiffies{0};
  long prev_idlejiffies{0};
  long activejiffies{0};
  long idlejiffies{0};

  std::vector<int> active_procs{kUser_, kNice_,    kSystem_, kSystem_,
                                kIRQ_,  kSoftIRQ_, kSteal_};
  std::vector<int> idle_procs{kIdle_, kIOwait_};

  for (auto ap : active_procs) prev_activejiffies += utilization_[ap];
  for (auto ip : idle_procs) prev_idlejiffies += utilization_[ip];

  std::vector<std::string> all_procs = LinuxParser::CpuUtilization();
  Utilization(all_procs);

  for (auto ap : active_procs) activejiffies += utilization_[ap];
  for (auto ip : idle_procs) idlejiffies += utilization_[ip];

  total_delta =
      (activejiffies + idlejiffies) - (prev_activejiffies + prev_idlejiffies);
  idle_delta = idlejiffies - prev_idlejiffies;

  return (float)(total_delta - idle_delta) / total_delta;
}