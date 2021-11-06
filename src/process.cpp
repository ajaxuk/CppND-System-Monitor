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
std::string Process::Command() const { return command_; }
long int Process::UpTime() const { return uptime_; }

void Process::Command(std::string command) { command_ = command; }
void Process::UpTime(long int uptime) { uptime_ = uptime; };
void Process::Pid(int pid) { pid_ = pid; }
void Process::User(std::string user) { user_ = user; }
void Process::CpuUtilization(float cpuutilization) {
  cpuutilization_ = cpuutilization;
}
void Process::Ram(std::string ram) { ram_ = ram; }

// DONE: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return this->cpuutilization_ < a.cpuutilization_;
}