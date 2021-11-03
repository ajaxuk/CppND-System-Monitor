#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() const { return pid_; }
string Process::User() const { return user_; }
float Process::CpuUtilization() const { return cpuutilization_; }
string Process::Ram() const { return ram_; }

void Process::Pid(int pid) { pid_ = pid; }
void Process::User(std::string user) { user_ = user; }
void Process::CpuUtilization(float cpuutilization) {
  cpuutilization_ = cpuutilization;
}
void Process::Ram(std::string ram) { ram_ = ram; }

// void Process::Command(std::string command){};

// void Process::UpTime(long int uptime){};

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a [[maybe_unused]]) const {
  return true;
}