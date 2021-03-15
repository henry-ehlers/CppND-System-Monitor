#include <string>
#include <iostream>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
  
  // Initialize all variables needed
  int t_hours, t_minutes, t_seconds;
  std::string s_hours, s_minutes, s_seconds;
  std::string out_string;
  
  // Calculate Integer values
  t_hours    = seconds / 60 / 60;
  t_minutes  = (seconds / 60) % 60;
  t_seconds  = seconds % 60;
  
  // Convert to string
  s_hours   = std::to_string(t_hours);
  s_minutes = std::to_string(t_minutes);
  s_seconds = std::to_string(t_seconds);
  s_seconds.insert(0, 2 - s_seconds.length(), '0'); // Ensure seconds update properly
    
  // Define final output string
  out_string = s_hours + ":" + s_minutes + ":" + s_seconds; 
  return out_string;
}