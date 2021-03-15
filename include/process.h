#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  bool operator>(Process const& a) const;

  // TODO: Declare any necessary private members
 private:
  int pid{-1};
  int uid{-1};
  float cpu_utilization{-1.0};
  int ram_utilization{-1};
  long int up_time{-1};
  std::string username{"None"};
  std::string command{"None"};
  
  void Command(int pid);
  void Pid(int pid);                               
  void User(int uid);
  void UID(int pid);
  void CpuUtilization(int pid);                 
  void Ram(int pid);                       
  void UpTime(int pid);
  
};

#endif