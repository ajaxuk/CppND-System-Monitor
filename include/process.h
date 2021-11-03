#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid() const;                         // TODO: See src/process.cpp
  std::string User() const;                // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() const;            // TODO: See src/process.cpp
  std::string Ram() const;                 // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  void Pid(int pid);
  void User(std::string user);
  void CpuUtilization(float cpuutilization);
  void Ram(std::string ram);
  // void Command(std::string command);

  //
  // void UpTime(long int uptime);

  // TODO: Declare any necessary private members
 private:
  int pid_{};
  std::string user_;
  float cpuutilization_{};
  std::string ram_;
  /*


   std::string command_;
   float cpuutilization_;

   long int uptime_;
   */
};

#endif