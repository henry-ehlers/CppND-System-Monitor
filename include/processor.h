#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
    
    float Utilization();  // TODO: See src/processor.cpp
    float Calculate_Utilization(const std::vector<int> &cpu_usages);
    int Sum_Vector_Indexes(const std::vector<int> &some_vector, const std::vector<int> &some_indeces);
    int Calculate_Active_Time(const std::vector<int>  &cpu_usages);
    int Calculate_Idle_Time(const std::vector<int>  &cpu_usages);

  // TODO: Declare any necessary private members
 private:
    
    std::vector<int> idle_cpu_indeces{3, 4};
    std::vector<int> active_cpu_indeces{0, 1, 2, 5, 6, 7, 8, 9, 10};

    std::vector<int>& get_idle_cpu_indeces(){return idle_cpu_indeces;};
    std::vector<int>& get_active_cpu_indeces(){return active_cpu_indeces;};

};

#endif