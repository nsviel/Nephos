#include "CPU.h"

#include <Utility/Namespace.h>
#include <fstream>


namespace utl::hardware{

//Constructor / Destructor
CPU::CPU(){
  //---------------------------


  //---------------------------
}
CPU::~CPU(){}

//Main function
float CPU::get_temperature(){
  //---------------------------

  std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
  float temp;
  file >> temp;

  //---------------------------
  return temp / 1000.0; // The temperature is usually reported in millidegrees Celsius
}
std::string get_cpu_name(){
  //---------------------------

  std::ifstream cpuinfo("/proc/cpuinfo");
  std::string line;
  std::string cpu_name = "(unknown)";

  if(cpuinfo.is_open()){
    while(std::getline(cpuinfo, line)){
      // Look for the line that starts with "model name"
      if(line.find("model name") != std::string::npos){
        // Extract the CPU name from the line
        size_t colon_pos = line.find(':');
        if(colon_pos != std::string::npos){
          cpu_name = line.substr(colon_pos + 2); // Skip the ": " part
          break;
        }
      }
    }
    cpuinfo.close();
  }

  //---------------------------
  return cpu_name;
}

int get_number_of_cpus(){
  //---------------------------

  std::ifstream cpuinfo("/proc/cpuinfo");
  std::string line;
  std::set<int> cpu_ids;

  if(cpuinfo.is_open()){
    while(std::getline(cpuinfo, line)){
      // Look for the line that starts with "processor"
      if(line.find("processor") != std::string::npos){
        // Extract the processor ID from the line
        size_t colon_pos = line.find(':');
        if(colon_pos != std::string::npos){
          int cpu_id = std::stoi(line.substr(colon_pos + 1));
          cpu_ids.insert(cpu_id);
        }
      }
    }
    cpuinfo.close();
  }

  //---------------------------
  return cpu_ids.size();
}

}
