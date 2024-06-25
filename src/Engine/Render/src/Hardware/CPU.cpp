#include "CPU.h"

#include <fstream>


namespace rnd::hardware{

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

}
