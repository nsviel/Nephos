#include "Profiler.h"

#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace prf::hardware{

//Constructor / Destructor
Profiler::Profiler(prf::Node* node_profiler){
  //---------------------------

  this->prf_struct = node_profiler->get_prf_struct();
  this->cpu_device = new prf::hardware::CPU(node_profiler);
  this->gpu_device = new prf::hardware::GPU(node_profiler);

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::init(){
  //---------------------------

  //CPU
  cpu_device->collect_cpu_info();

  //GPU
  gpu_device->collect_gpu_info();
  gpu_device->collect_vulkan_info();

  //---------------------------
}
void Profiler::loop(){
  //---------------------------

  //CPU
  cpu_device->collect_cpu_info();

  //GPU
  gpu_device->collect_gpu_info();

  //---------------------------
}

}
