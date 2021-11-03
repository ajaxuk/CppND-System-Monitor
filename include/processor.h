#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

class Processor {
 public:
  float Utilization();

  void Utilization(std::vector<std::string> &utilization);

  // TODO: See src/processor.cpp
  // TODO: Declare any necessary private members

 private:
  // Store values taken from fields listed in the first line of /proc/stat
  // these will be used to calculte the delat from the previous time they were
  // read to give a more accurate picture of overall CPU tilisiation. user ||
  // nice || system || idle || iowait || irq|| softirq || steal || guest ||
  // guest_nice
  // std::vector<long> utilization_(10,0);    <= Why doesnt this work?
  std::vector<long> utilization_{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};

#endif