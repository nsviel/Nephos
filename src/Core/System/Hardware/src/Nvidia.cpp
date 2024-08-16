#include "Nvidia.h"


namespace sys::hardware{

//Constructor / Destructor
Nvidia::Nvidia(){
  //---------------------------

  nvmlInit();

  //---------------------------
  this->init();
}
Nvidia::~Nvidia(){
  //---------------------------

  nvmlShutdown();

  //---------------------------
}

//Main function
void Nvidia::init(){
  //---------------------------

  nvmlReturn_t result = nvmlDeviceGetHandleByIndex(0, &device);
  if(result != NVML_SUCCESS){
    return;
  }

  //---------------------------
}

//Subfunction
float Nvidia::get_total_consumption(){
  unsigned long long energy;
  //---------------------------

  nvmlReturn_t result = nvmlDeviceGetTotalEnergyConsumption(device, &energy);
  if(result != NVML_SUCCESS){
    return -1;
  }

  //---------------------------
  return (float)energy / 1000000;
}
float Nvidia::get_power_usage(){
  unsigned int power;
  //---------------------------

  nvmlReturn_t result = nvmlDeviceGetPowerUsage(device, &power);
  if(result != NVML_SUCCESS){
    return -1;
  }

  //---------------------------
  return (float)power / 1000.0f;
}
int Nvidia::get_temperature(){
  unsigned int temp;
  //---------------------------

  nvmlReturn_t result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
  if(result != NVML_SUCCESS){
    return -1;
  }

  //---------------------------
  return temp;
}
int Nvidia::get_temperature_max_slowdown(){
  unsigned int temp;
  //---------------------------

  nvmlReturn_t result = nvmlDeviceGetTemperatureThreshold(device, NVML_TEMPERATURE_THRESHOLD_SLOWDOWN, &temp);
  if(result != NVML_SUCCESS){
    return -1;
  }

  //---------------------------
  return temp;
}
int Nvidia::get_temperature_max_shutdown(){
  unsigned int temp;
  //---------------------------

  nvmlReturn_t result = nvmlDeviceGetTemperatureThreshold(device, NVML_TEMPERATURE_THRESHOLD_SHUTDOWN, &temp);
  if(result != NVML_SUCCESS){
    return -1;
  }

  //---------------------------
  return temp;
}
int Nvidia::get_temperature_max_gpu(){
  unsigned int temp;
  //---------------------------

  nvmlReturn_t result = nvmlDeviceGetTemperatureThreshold(device, NVML_TEMPERATURE_THRESHOLD_GPU_MAX, &temp);
  if(result != NVML_SUCCESS){
    return -1;
  }

  //---------------------------
  return temp;
}
int Nvidia::get_fan_speed(){
  unsigned int speed;
  //---------------------------

  nvmlReturn_t result = nvmlDeviceGetFanSpeed(device, &speed);
  if(result != NVML_SUCCESS){
    return -1;
  }

  //---------------------------
  return speed;
}

}
