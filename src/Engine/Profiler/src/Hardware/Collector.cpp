#include "Collector.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace prf::hardware{

//Constructor / Destructor
Collector::Collector(prf::Node* node_profiler){
  //---------------------------

  vk::Node* node_vulkan = node_profiler->get_node_vulkan();

  this->vk_struct = node_vulkan->get_vk_struct();
  this->prf_struct = node_profiler->get_prf_struct();
  this->utl_nvidia = new utl::hardware::Nvidia();
  this->utl_cpu = new utl::hardware::CPU();

  //---------------------------
}
Collector::~Collector(){}

//Profiler vulkan info
void Collector::collect_info(){
  //---------------------------



  //---------------------------
}

//Subfunction
void Collector::collect_gpu_info(){
  //---------------------------


  //---------------------------
}
void Collector::collect_cpu_info(){
  //---------------------------


  //---------------------------
}
void Collector::collect_vulkan_device(){
  //---------------------------


  //---------------------------
}
void Collector::collect_vulkan_queue(){
  //---------------------------


  //---------------------------
}
void Collector::add_queue(vk::queue::structure::Queue& queue, int type){
  //---------------------------



  //---------------------------
}


}
