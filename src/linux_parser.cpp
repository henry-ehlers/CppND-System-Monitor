#include <dirent.h>
#include <linux_parser.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <regex>
#include <iterator>
#include <stdio.h>
#include <math.h>
#include <boost/algorithm/string.hpp>
#include <unistd.h>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  
  // String objects for file reading and output
  std::string os_system;
  std::string line;
  
  // Regex Objects required
  std::regex rgx("^PRETTY_NAME=\"(.+)\"$");
  std::smatch linematch;

  // File Handling
  std::string targetfile = "/etc/os-release";
  std::ifstream myfile;
  myfile.open (targetfile);
  assert(myfile);

  // Iterate over each line until file ends or os_regex_line found
  while (!std::regex_match(line, linematch, rgx)) {
    getline(myfile, line);
  };
  os_system = linematch[1]; //returns only the match group and 'destroys' the linematch object
  myfile.close();
  return os_system;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  std::string filename = "/proc/version";
  std::string line;
  std::string kernel;

  std::ifstream myfile;
  myfile.open (filename);
  assert(myfile);
  
  std::regex rgx("^Linux\\s+version\\s([\\w\\.\\-]+)\\s.*$");
  std::smatch linematch;
  
  while (!std::regex_match(line, linematch, rgx)) {
    getline(myfile, line);
  };
  kernel = linematch[1];
  myfile.close();

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

float LinuxParser::CalculateMemoryUtilization(const int& memtotal, const int& memfree) {
  float memory_utilization = 1.0 - (float) memfree / (float) memtotal;
  return memory_utilization;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  
  // Vector to store free and total memory
  std::vector<int> memory_utilization = {-1, -1};
  
  // Regular Expression needed to grab info from line
  std::regex rgx("^\\w+\\:\\s+(\\d+)\\s+.*$");
  std::smatch memory_info;
  
  // Prepare strings required
  std::string filename = "/proc/meminfo";
  std::string fileline;
  
  // Open file and ensure it exists
  std::ifstream myfile;
  myfile.open(filename);
  assert(myfile);

  for (int linenumber = 0; linenumber < memory_utilization.size(); linenumber++) {
    getline(myfile, fileline);
    assert(std::regex_match(fileline, memory_info, rgx));
    memory_utilization[linenumber] = std::stof(memory_info[1]);
  }
  myfile.close();
  
  return LinuxParser::CalculateMemoryUtilization(memory_utilization[0], memory_utilization[1]);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  std::string filename = "/proc/uptime";
  std::string line;
  
  std::regex rgx("^([\\d\\.]+)\\s+[\\d+\\.]+\\s*$");
  std::smatch linematch;
  
  std::ifstream myfile;
  myfile.open(filename);
  assert(myfile);
  
  getline(myfile, line);
  assert(std::regex_match(line, linematch, rgx));
  
  return std::stol(linematch[1]); 
}

// // TODO: Read and return the number of jiffies for the system
// long LinuxParser::Jiffies() { return 0; }

// // TODO: Read and return the number of active jiffies for a PID
// // REMOVE: [[maybe_unused]] once you define the function
// long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// // TODO: Read and return the number of active jiffies for the system
// long LinuxParser::ActiveJiffies() { return 0; }

// // TODO: Read and return the number of idle jiffies for the system
// long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<int> LinuxParser::CpuUtilization() {
  std::string line;
  std::vector<int> cpu_usages(10, -1); 
  std::ifstream myfile;
  myfile.open ("/proc/stat");
  assert(myfile);
  getline(myfile, line);
  char char_array[line.length()];
  strcpy(char_array, line.c_str());
  char *token = strtok(char_array, " "); 
  for (int index = 0; index < cpu_usages.size(); index ++) {
    if (index > 0) {
      cpu_usages[index-1] = std::stoi(token);
    };
    token = strtok(NULL, " "); 
  }
  myfile.close();
  return cpu_usages; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::regex rgx("^processes\\s+(\\d+)");
  std::string filename = "/proc/stat";
  return std::stoi(LinuxParser::LineByLineRegexGetter(filename, rgx));
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::regex rgx("^procs_running\\s+(\\d+)");
  std::string filename = "/proc/stat";
  return std::stoi(LinuxParser::LineByLineRegexGetter(filename, rgx));
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::Command(int pid) { 
  std::string file_location = "/proc/" + std::to_string(pid) + "/cmdline";
  std::string cmdline{""};
  std::ifstream myfile;
  myfile.open(file_location);
  assert(myfile);
  
  getline(myfile, cmdline);
  myfile.close();
  return cmdline; 
}

float LinuxParser::Cpu(int pid, int uptime) {
  std::string file_location = "/proc/" + std::to_string(pid) + "/stat";
  std::vector<int> cpu_times = {-1, -1, -1, -1, -1};
  
  std::string line;
  std::fstream myfile;
  myfile.open(file_location);
  assert(myfile);
  
  getline(myfile, line);
  std::vector<std::string> line_strs;
  boost::split(line_strs, line, boost::is_any_of("\t "));
  myfile.close();
  
  int utime   = std::stoi(line_strs[13]);
  int stime   = std::stoi(line_strs[14]);
  int cutime  = std::stoi(line_strs[15]);
  int cstime  = std::stoi(line_strs[17]);
  int startt  = std::stoi(line_strs[21]);
  float HERTZ = sysconf(_SC_CLK_TCK);
  
  int total_time = utime + stime + cutime + cstime;
  float seconds  = (float)uptime - ((float)startt / HERTZ);
  float cpu_util = ((float)total_time / HERTZ ) / seconds;
    
  return cpu_util;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
int LinuxParser::Ram(int pid) { 
  std::string file_location = "/proc/" + std::to_string(pid) + "/status";
  std::regex rgx("^VmSize:\\s+(\\d+)\\s+kB\\s?$");
  std:string ram_useage = LinuxParser::LineByLineRegexGetter(file_location, rgx);
  return std::stol(ram_useage) / 1000; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  std::string file_location = "/proc/" + std::to_string(pid) + "/status";
  std::regex rgx("^Uid:\\s+(\\d+)\\s+.+$");
  return LinuxParser::LineByLineRegexGetter(file_location, rgx); 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int uid) { 
  std::string rgx_expr = "^([\\w\\d]+):x+:" + std::to_string(uid) + ":" + std::to_string(uid) + ".+$";
  std::regex rgx(rgx_expr);
  std::string file_location = "/etc/passwd";
  return LinuxParser::LineByLineRegexGetter(file_location, rgx); 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid) { 

  // Intialize the two file reading variables needed
  std::string ss_key;
  std::string line;

  // Setup filestream and ensure it exists
  std::ifstream filestream("/proc/" + std::to_string(pid) + "/stat") ;
  assert(filestream.is_open());
   
  while ( std::getline(filestream,line) ) {
    std::istringstream linestream(line);
    int index = 0;
    while(linestream >> ss_key ) {
      if (index == 21) {
        long int system_uptime =  LinuxParser::UpTime();
        long int process_uptime = system_uptime - std::stol(ss_key) / sysconf(_SC_CLK_TCK);
        return process_uptime;
      }
      index++;
    }
  }
  
}

std::string LinuxParser::LineByLineRegexGetter(std::string file_location, std::regex rgx){
  //std::cout  << file_location << "\n";
  
  // reate File object and ensure it exists
  std::ifstream myfile;
  std::string line;
  myfile.open(file_location);
  assert(myfile);
  
  // Iterate over each line of file until a hit is obtained
  std::smatch rgx_match;
  while (!std::regex_match(line, rgx_match, rgx)) {
    getline(myfile, line);
  }
  myfile.close();
  
  // Return only the Regex Catch
  return rgx_match[1]; 
}
