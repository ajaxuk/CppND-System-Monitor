#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below

I dont beleive the getters / setters are really necessary here..

*/
class Process {
 public:
  int Pid() const;               // DONE: See src/process.cpp
  std::string User() const;      // DONE: See src/process.cpp
  std::string Command() const;   // DONE: See src/process.cpp
  float CpuUtilization() const;  // DONE: See src/process.cpp
  std::string Ram() const;       // DONE: See src/process.cpp
  long int UpTime() const;       // DONE: See src/process.cpp

  bool operator<(Process const& a) const;  // DONE: See src/process.cpp

  void Pid(int pid);
  void User(std::string user);
  void CpuUtilization(float cpuutilization);
  void Ram(std::string ram);
  void Command(std::string command);
  void UpTime(long int uptime);

  // DONE: Declare any necessary private members
 private:
  int pid_{};
  std::string user_;
  float cpuutilization_{};
  std::string ram_;
  std::string command_;
  long int uptime_;
};

#endif