#include "Profiler.h"

#include <Profiler/Namespace.h>
#include <nvml.h>


namespace prf::temp{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------

  this->name = "Temperature";

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::reset(){
  //---------------------------



  //---------------------------
}

//Subfunction
float Profiler::find_CPU_temperature(){
  //---------------------------

  std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
  float temp;
  file >> temp;

  //---------------------------
  return temp / 1000.0; // The temperature is usually reported in millidegrees Celsius
}

float Profiler::find_GPU_temperature(){
  nvmlDevice_t device;
  //---------------------------

  nvmlInit();
  nvmlDeviceGetHandleByIndex(0, &device);

  unsigned int temp;
  nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);

  unsigned long long energy;
  nvmlDeviceGetTotalEnergyConsumption(device, &energy); //mJ

  unsigned int speed;
  nvmlDeviceGetFanSpeed(device, &speed);

  unsigned int power;
  nvmlDeviceGetPowerUsage(device, &power); // in mW
  nvmlShutdown();

  say(energy);

  //---------------------------
  return static_cast<float>(temp);
}

}
