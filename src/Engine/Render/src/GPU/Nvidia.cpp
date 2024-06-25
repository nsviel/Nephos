#include "Nvidia.h"

#include <nvml.h>


namespace prf::temp{

//Constructor / Destructor
Nvidia::Nvidia(){
  //---------------------------

  nvmlInit();

  //---------------------------
}
Nvidia::~Nvidia(){
  //---------------------------

  nvmlShutdown();

  //---------------------------
}

//Main function
float Nvidia::get_total_consumption(){
  unsigned long long energy;
  //---------------------------

  nvmlDevice_t device;
  nvmlReturn_t result;

  result = nvmlDeviceGetHandleByIndex(0, &device);
  if(result != NVML_SUCCESS){
    return -1;
  }
  result = nvmlDeviceGetTotalEnergyConsumption(device, &energy);
  if(result != NVML_SUCCESS){
    return -1;
  }

  //---------------------------
  return (float)energy / 1000;
}
int Nvidia::get_temperature(){
  unsigned int temp;
  //---------------------------

  nvmlDevice_t device;
  nvmlReturn_t result;

  result = nvmlDeviceGetHandleByIndex(0, &device);
  if(result != NVML_SUCCESS){
    return -1;
  }
  result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
  if(result != NVML_SUCCESS){
    return -1;
  }

  //---------------------------
  return temp;
}
int Nvidia::get_fan_speed(){
  unsigned int speed;
  //---------------------------

  nvmlDevice_t device;
  nvmlReturn_t result;

  result = nvmlDeviceGetHandleByIndex(0, &device);
  if(result != NVML_SUCCESS){
    return -1;
  }
  result = nvmlDeviceGetFanSpeed(device, &speed);
  if(result != NVML_SUCCESS){
    return -1;
  }

  //---------------------------
  return speed;
}
int Nvidia::get_power_usage(){
  unsigned int power;
  //---------------------------

  nvmlDevice_t device;
  nvmlReturn_t result;

  result = nvmlDeviceGetHandleByIndex(0, &device);
  if(result != NVML_SUCCESS){
    return -1;
  }
  result = nvmlDeviceGetPowerUsage(device, &power);
  if(result != NVML_SUCCESS){
    return -1;
  }

  //---------------------------
  return power;
}

//Subfunction

}
