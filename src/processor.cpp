#include "processor.h"
#include "string"
#include <iostream>
#include <fstream>
#include <regex>
#include <assert.h>
#include <iterator>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {  
    int cpu_usage;
    std::vector<int> cpu_usages(10, -1); 
    std::regex line_exp("^cpu\\s+.");
    std::regex digit_exp("(\\d+)");
    std::smatch match;

    std::ifstream myfile;
    myfile.open ("/proc/stat");
    if (myfile) {
        std::string line;
        while (getline(myfile, line)) {
            if (std::regex_search(line, match, line_exp)) {
                std::sregex_iterator iter(line.begin(), line.end(), digit_exp);
                int index = 0;
                while (index > 10) {
                    cpu_usages[index] = std::stoi((*iter)[0]);
                    ++iter;
                    ++index;
                }
                break;
            };
        }
    }
    myfile.close();
	cpu_usage = Calculate_Utilization(cpu_usages);
    return cpu_usage; 
}

float Processor::Calculate_Utilization(const std::vector<int> &cpu_usages) {
    assert (cpu_usages.size() == 10);
  	int active_time = Calculate_Active_Time(cpu_usages);
    int idle_time   = Calculate_Idle_Time(cpu_usages);
  	float cpu_utilization = active_time / (active_time + idle_time);
    return cpu_utilization;
}

int Processor::Calculate_Idle_Time(const std::vector<int>  &cpu_usages){
    int idle_time = Sum_Vector_Indexes(cpu_usages, get_idle_cpu_indeces());
    return idle_time;
}  

int Processor::Calculate_Active_Time(const std::vector<int>  &cpu_usages) {
    int active_time = Sum_Vector_Indexes(cpu_usages, get_active_cpu_indeces());
    int active_time;
}

int Processor::Sum_Vector_Indexes(const std::vector<int> &some_vector, const std::vector<int> &some_indeces){
    int sum_across_indeces = 0;
    for (int some_index : some_indeces) {
        sum_across_indeces += some_vector[some_index];
    }
    return sum_across_indeces;
}


