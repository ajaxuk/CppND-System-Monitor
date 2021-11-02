#include "processor.h"

#include <string>
#include <vector>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { return 0.0; }

/*
long total_delta;
long idle_delta;

std::vector<std::string> stats = LinuxParser::CpuUtilization();
long prev_activejiffies = cpu_stats_[0] + cpu_stats_[1] + cpu_stats_[2] +
                          cpu_stats_[5] + cpu_stats_[6] + cpu_stats_[7] +
                          cpu_stats_[8] + cpu_stats_[9];
long prev_idlejiffies = cpu_stats_[3] + cpu_stats_[4];
SetStats(stats);
long activejiffies = cpu_stats_[0] + cpu_stats_[1] + cpu_stats_[2] +
                     cpu_stats_[5] + cpu_stats_[6] + cpu_stats_[7] +
                     cpu_stats_[8] + cpu_stats_[9];
long idlejiffies = cpu_stats_[3] + cpu_stats_[4];

total_delta =
    (activejiffies + idlejiffies) - (prev_activejiffies + prev_idlejiffies);
idle_delta = idlejiffies - prev_idlejiffies;

return (float)(total_delta - idle_delta) / total_delta;
}

void Processor::SetStats(std::vector<std::string> &stats) {
for (int i = 0; i < 10; i++)

{
  cpu_stats_[i] = std::stol(stats[i]);
}
}
*/