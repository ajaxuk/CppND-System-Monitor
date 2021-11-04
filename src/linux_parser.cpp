#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  // /proc/meminfo is three columns Description / Amount / Unit
  // we need the MemTotal: and MemFree: amounts

  string desc, amnt, unit;
  long memtotal{0}, memfree{0};
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> desc >> amnt >> unit) {
        if (desc == "MemTotal:") {
          memtotal = std::stol(amnt);
        }
        if (desc == "MemFree:") {
          memfree = std::stol(amnt);
        }

        if (memtotal > 0 && memfree > 0) {
          stream.close();
          return (float)(memtotal - memfree) / memtotal;  // memory utilisation
        }
      }
    }
  }
  return 0.0;
}

// DONE (TESTED vs htop): Read and return the system uptime
// There are two entries in uptime. We only need the first.
long LinuxParser::UpTime() {
  string uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return std::stol(uptime);  // convert string to long
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> cpu_util{};
  string item;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> item;  // dispose of first item which is CPU label. Maybe
                         // later add checking to make sure first line is CPU...
    for (int i = kUser_; i <= kGuestNice_; i++) {
      linestream >> item;
      cpu_util.push_back(item);
    }
  }

  return cpu_util;
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string key;
  string line;
  string value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      {
        linestream >> key >> value;

        if (key == "processes") {
          stream.close();
          return stoi(value);
        }
      }
    }
  }
  return 0;
}

// This number is retrieved from /proc/cat and is labelled 'processes'
// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string key;
  string line;
  string value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      {
        linestream >> key >> value;

        if (key == "procs_running") {
          stream.close();
          return stoi(value);
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string key;
  string line;
  string value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> value;
      return value;
    }
  }

  return string();
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string key;
  string line;
  string value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      {
        linestream >> key >> value;

        if (key == "VmSize:") {
          stream.close();
          return value;
        }
      }
    }
  }

  return string();
}

// DONE: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string key;
  string line;
  string value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      {
        linestream >> key >> value;

        if (key == "Uid:") {
          stream.close();
          return value;
        }
      }
    }
  }

  return string();
}

// DONE: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  std::string uid = Uid(pid);

  string user;
  string line;
  string value1;
  string value2;

  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      {
        linestream >> user >> value1 >> value2;

        if (value2 == uid) {  // rememebr to change back from 1000 to uid...
          stream.close();
          return user;
        }
      }
    }
  }

  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string key;
  string line;
  string value;
  int pos = 22;
  int cnt = 0;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      {
        while (cnt++ < pos) {
          linestream >> key;
        }

        stream.close();

        return std::stol(key) /
               sysconf(_SC_CLK_TCK);  // to convert to seconds from ticks
      }
    }
  }

  return 0;
}

float LinuxParser::ProcCpu(int pid) {
  std::vector<std::string> item;
  std::string line;
  std::string key;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      {
        for (int i = 0; i < 22; i++) {
          linestream >> key;
          item.push_back(key);
        }
        // https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
        long up_time = UpTime();
        long utime = std::stol(item[13]) / sysconf(_SC_CLK_TCK);
        long stime = std::stol(item[14]) / sysconf(_SC_CLK_TCK);
        long cutime = std::stol(item[15]) / sysconf(_SC_CLK_TCK);
        long cstime = std::stol(item[16]) / sysconf(_SC_CLK_TCK);
        long start_time = std::stol(item[21]) / sysconf(_SC_CLK_TCK);
        ;
        stream.close();

        long total_time = utime + stime;
        total_time += cutime + cstime;  // incldue children processes
        long seconds = up_time - start_time;

        return ((float)total_time / seconds);
      }
    }
  }

  return 0.0;
}