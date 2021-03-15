#include "processor.h"
#include "linux_parser.h"
#include "string"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <iterator>
#include <vector>
#include <string.h>
#include <cstring>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {  
  std::vector<int> cpu_usages = LinuxParser::CpuUtilization();
  cpu_utilization = Processor::Calculate_Utilization(cpu_usages);
  return this->cpu_utilization;
}

float Processor::Calculate_Utilization(const std::vector<int> &cpu_usages) {
  assert (cpu_usages.size() == 10);
  int active_time = Processor::Calculate_Active_Time(cpu_usages);
  int idle_time   = Processor::Calculate_Idle_Time(cpu_usages);
  float cpu_utilization = (float)active_time / ((float)active_time + (float)idle_time);
  return cpu_utilization;
}

int Processor::Calculate_Idle_Time(const std::vector<int>  &cpu_usages){
    int idle_time = Processor::Sum_Vector_Indexes(cpu_usages, Processor::get_idle_cpu_indeces());
    return idle_time;
}  

int Processor::Calculate_Active_Time(const std::vector<int>  &cpu_usages) {
    int active_time = Processor::Sum_Vector_Indexes(cpu_usages, Processor::get_active_cpu_indeces());
    return active_time;
}

int Processor::Sum_Vector_Indexes(const std::vector<int> &some_vector, const std::vector<int> &some_indeces){
    int sum_across_indeces = 0;
    for (int some_index : some_indeces) {
        sum_across_indeces += some_vector[some_index];
    }
    return sum_across_indeces;
}