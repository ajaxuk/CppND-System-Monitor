#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

using std::filesystem::directory_iterator;

// Generic Linux Parser that accepts a vector of ints (sequential order small to
// large) to represent the loctions for a line to be retrieved and returns a
// string vector of the values retrieved.
void LinuxParser::GenericLineParse(std::string const filepath,
                                   std::vector<int> const& pos,
                                   std::vector<string>& val) {
  string line;
  int cnt = 0;  // used to keep track of position in linestream
  string not_required;
  string required;
  std::ifstream stream(filepath);
  if (stream.is_open()) {
  (std::getline(stream, line));
      std::istringstream linestream(line);
      {
        for (auto p : pos) {
          while (cnt < p) {
          linestream >> not_required;
          cnt++;}
          linestream >> required;
          cnt++;
          val.emplace_back(required);
        }
      }
  }
}

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
  string filelocation{kProcDirectory + kVersionFilename};
  vector<string> kernel{};
  vector<int> positions = {2};  // (third item is kernel 0,1,2,3 vector numbering)

  GenericLineParse(filelocation, positions, kernel);

  return kernel.back();
}

// DONE: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  string dir_name;

  for (const auto& dir : directory_iterator(kProcDirectory)) {
    dir_name = dir.path().filename().string();
    if (std::all_of(dir_name.begin(), dir_name.end(), isdigit)) {
      pids.emplace_back(std::stoi(dir_name));
    }
  }
  /*
    // OLD CODE
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
    */
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
  string filelocation{kProcDirectory + kUptimeFilename};
  vector<string> uptime{};
  vector<int> positions = {0};  // first item in file

  GenericLineParse(filelocation, positions, uptime);

  return std::stol(uptime.back());
}

// DONE: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  return IdleJiffies()+ActiveJiffies(); }  // not used

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  

  long total_active_jiffies{};

  // 14=utime, 15=stime, 16=cutime, 17=cstime
  // https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
  vector<int> active_jiffies{14, 15, 16, 17,  18};

  string filelocation{kProcDirectory + std::to_string(pid) + kStatFilename};
  vector<string> active_Jiffy_values{};
  
  GenericLineParse(filelocation,active_jiffies,active_Jiffy_values);

  for (auto & ajv : active_Jiffy_values)
    total_active_jiffies += std::stol(ajv);
  
  return total_active_jiffies; }


// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  
  long total_active_jiffies{};

  vector<int> active_jiffies{kUser_, kNice_, kSystem_,
                                kIRQ_,  kSoftIRQ_, kSteal_};



  std::for_each(active_jiffies.begin(), active_jiffies.end(), [](int &n){ n+=1; }); // +1 becasue stat file starts with cpu column

  string filelocation{kProcDirectory + kStatFilename};
  vector<string> active_Jiffy_values{};
  
  GenericLineParse(filelocation,active_jiffies,active_Jiffy_values);

  for (auto & ajv : active_Jiffy_values)
    total_active_jiffies += std::stol(ajv);
  
  return total_active_jiffies; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  
  
  long total_idle_jiffies{};

  vector<int> idle_jiffies{kIdle_, kIOwait_};



  std::for_each(idle_jiffies.begin(), idle_jiffies.end(), [](int &n){ n+=1; }); // +1 becasue stat file starts with cpu column

  string filelocation{kProcDirectory + kStatFilename};
  vector<string> idle_Jiffy_values{};
  
  GenericLineParse(filelocation,idle_jiffies,idle_Jiffy_values);

  for (auto & ajv : idle_Jiffy_values)
    total_idle_jiffies += std::stol(ajv);
  
  return total_idle_jiffies; }
  
// DONE Read and return CPU utilization (Does it but not needed)
vector<string> LinuxParser::CpuUtilization() {

  // not used since utilisation usies the active jiffies and idle jiffies parser functions
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

          return std::to_string((int)(std::stof(value) / 1024));
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

        stream.close();

        long total_time = utime + stime;
        total_time += cutime + cstime;  // incldue children processes
        long seconds = up_time - start_time;

        return ((float)total_time /
                seconds);  // already multiplied by 100 in ncurses_display.cpp
      }
    }
  }

  return 0.0;
}