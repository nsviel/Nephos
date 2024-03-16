#include "Info.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Info::Info(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Info::~Info(){}

//Profiler vulkan info
void Info::fill_info(){
  prf::vulkan::Profiler* prf_vulkan = struct_vulkan->profiler->prf_vulkan;
  //---------------------------

  this->fill_vulkan_info(prf_vulkan);
  this->fill_vulkan_device(prf_vulkan);

  //---------------------------
}
void Info::fill_vulkan_info(prf::vulkan::Profiler* prf_vulkan){
  prf::vulkan::Info* info_vulkan = prf_vulkan->get_info();
  //---------------------------

  info_vulkan->selected_gpu = struct_vulkan->device.physical_device.name;

  //---------------------------
}
void Info::fill_vulkan_device(prf::vulkan::Profiler* prf_vulkan){
  vector<prf::vulkan::Device>& vec_device = prf_vulkan->get_info_device();
  //---------------------------

  for(int i=0; i<struct_vulkan->instance.vec_physical_device.size(); i++){
    vk::structure::Physical_device& physical_device = struct_vulkan->instance.vec_physical_device[i];
    prf::vulkan::Device device_info;

    device_info.name = physical_device.name;
    device_info.has_extension_support = physical_device.has_extension_support;
    device_info.discrete_gpu = physical_device.discrete_gpu;
    device_info.max_image_dim = physical_device.max_image_dim;
    device_info.vendorID = physical_device.vendorID;

    for(int i=0; i<physical_device.vec_queue_family.size(); i++){
      prf::vulkan::Queue_family queue_family;
      queue_family.nb_queue = physical_device.vec_queue_family[i].nb_queue;
      queue_family.graphics = physical_device.vec_queue_family[i].graphics;
      queue_family.compute = physical_device.vec_queue_family[i].compute;
      queue_family.transfer = physical_device.vec_queue_family[i].transfer;
      queue_family.sparseBinding = physical_device.vec_queue_family[i].sparseBinding;
      queue_family.presentation = physical_device.vec_queue_family[i].presentation;

      device_info.vec_queue_family.push_back(queue_family);
    }

    vec_device.push_back(device_info);
  }

  //---------------------------
}

//Subfunction
string Info::get_gpu_name(){
  return struct_vulkan->device.physical_device.name;
}
vec4* Info::get_color_background(){
  return &struct_vulkan->param.background_color;
}
bool Info::is_gpu_discrete(){
  return struct_vulkan->device.physical_device.discrete_gpu;
}

}
