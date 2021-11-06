#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   // DONE: See src/system.cpp
  std::vector<Process>& Processes();  // DONE: See src/system.cpp
  float MemoryUtilization();          // DONE: See src/system.cpp
  long UpTime();                      // DONE: See src/system.cpp
  int TotalProcesses();               // DONE: See src/system.cpp
  int RunningProcesses();             // DONE: See src/system.cpp
  std::string Kernel();               // DONE: See src/system.cpp
  std::string OperatingSystem();      // DONE: See src/system.cpp

  // DONE: Define any necessary private members
 private:
  Processor cpu_ = {};                   // compoisiton:System "has a" cpu
  std::vector<Process> processes_ = {};  // composiiton: system has processes
};

#endif