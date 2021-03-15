#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) {
  Process::Pid(pid);
  Process::Command(pid);
  Process::User(pid);
  Process::Ram(pid);
  Process::UpTime(pid);
  Process::CpuUtilization(pid);
}

void Process::CpuUtilization(int pid) {
  cpu_utilization = LinuxParser::Cpu(pid, Process::UpTime());
}

void Process::UpTime(int pid) {
  up_time = LinuxParser::UpTime(pid)/sysconf(_SC_CLK_TCK);
}

void Process::Ram(int pid) {
  ram_utilization = LinuxParser::Ram(pid);
}

void Process::User(int pid) { 
  uid = std::stoi(LinuxParser::Uid(pid));
  username = LinuxParser::User(uid);
}

void Process::Pid(int new_pid) {
  pid = new_pid;
}

void Process::Command(int pid) {
  command = LinuxParser::Command(pid);
}

// TODO: Return this process's ID
int Process::Pid() {return pid;}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { return cpu_utilization; }

// TODO: Return the command that generated this process
string Process::Command() { return command; }

// TODO: Return this process's memory utilization
string Process::Ram() { return std::to_string(ram_utilization); }

// TODO: Return the user (name) that generated this process
string Process::User() { 
  return username; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return up_time; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return (Process::CpuUtilization() < a.CpuUtilization());
}

bool Process::operator>(Process const& a) const { 
  return (Process::CpuUtilization() > a.CpuUtilization());
}