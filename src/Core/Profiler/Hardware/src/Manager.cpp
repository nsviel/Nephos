#include "Manager.h"

#include <Profiler/Hardware/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::hardware{

//Constructor / Destructor
Manager::Manager(prf::hardware::Node* node_hardware){
  //---------------------------

  this->prf_struct = node_profiler->get_prf_struct();
  this->cpu_device = new prf::hardware::CPU(node_profiler);
  this->gpu_device = new prf::hardware::GPU(node_profiler);

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  cpu_device->collect_cpu_info();
  gpu_device->collect_gpu_info();
  gpu_device->collect_vulkan_info();

  //---------------------------
}
void Manager::loop(){
  //---------------------------

  cpu_device->collect_cpu_variable();
  gpu_device->collect_gpu_variable();

  //---------------------------
}

}
