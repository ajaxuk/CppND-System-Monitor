#include "processor.h"

#include <string>
#include <vector>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  long total_delta;
  long idle_delta;

  std::vector<std::string> stats = LinuxParser::CpuUtilization();
  long prev_activejiffies = LinuxParser::ActiveJiffies();
  long prev_idlejiffies = LinuxParser::IdleJiffies();
  SetStats(stats);
  long activejiffies = LinuxParser::ActiveJiffies();
  long idlejiffies = LinuxParser::IdleJiffies();

  total_delta =
      (activejiffies + idlejiffies) - (prev_activejiffies + prev_idlejiffies);
  idle_delta = idlejiffies - prev_idlejiffies;

  return (float)(total_delta - idle_delta) / total_delta;
}

void Processor::SetStats(std::vector<std::string> &stats) {

}
