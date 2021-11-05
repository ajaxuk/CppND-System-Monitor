#include "system.h"

#include <unistd.h>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
using std::set;
using std::size_t;
using std::string;
using std::vector;

/*You need to complete the mentioned TODOs in order to satisfy the rubric
criteria "The student will be able to extract and display basic data about the
system."

You need to properly format the uptime. Refer to the comments mentioned in
format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() {
  // Why do I need a CPU object ?
  return cpu_;
}

// DONE: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  // get list of the pids, we need a process object for each pid.

  std::vector<int> pids = LinuxParser::Pids();
  int process_number = pids.size();
  processes_.clear();  // empty the container to reload the processes.

  // Process* new_processes =
  //  new Process[process_number];  // dynamic array of objects through use of
  // pointers.

  // populate the memebr variables of each process
  for (int i = 0; i < process_number; i++) {
    Process p;
    p.Pid(pids[i]);
    p.User(LinuxParser::User(pids[i]));
    p.CpuUtilization(LinuxParser::ProcCpu(pids[i]));
    p.Ram(LinuxParser::Ram(pids[i]));
    p.UpTime(LinuxParser::UpTime(pids[i]));
    p.Command(LinuxParser::Command(pids[i]));

    processes_.push_back(p);
  }

  // sort processes according to CPU utilisation using overloaded operator '<'
  std::sort(processes_.begin(), processes_.end(),
            [](Process& a, Process& b) { return b < a; });

  // clean up / / release memory allocated on the heap
  // delete[] new_processes;
  return processes_;
}

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// DONE: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// DONE: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// DONE: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }