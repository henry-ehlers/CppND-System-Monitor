#include <string>
#include <iostream>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
    int t_hours, t_minutes, t_seconds;
    std::string out_string;
    t_hours    = seconds / 3600;
    t_minutes  = (seconds / 60) % 60;
    t_seconds  = (seconds % 60) % 60;
    out_string = std::to_string(t_hours) + ":" + std::to_string(t_minutes) + ":" + std::to_string(t_seconds); 
    return out_string;}