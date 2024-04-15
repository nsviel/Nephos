#include "Interface.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Interface::Interface(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Interface::~Interface(){}

//Profiler vulkan info
void Interface::fill_info(){
  prf::vulkan::Profiler* prf_vulkan = vk_struct->profiler->prf_vulkan;
  //---------------------------

  this->fill_vulkan_info(prf_vulkan);
  this->fill_vulkan_device(prf_vulkan);

  //---------------------------
}
void Interface::fill_vulkan_info(prf::vulkan::Profiler* prf_vulkan){
  prf::vulkan::Info* info_vulkan = prf_vulkan->get_info();
  //---------------------------

  info_vulkan->selected_gpu = vk_struct->device.physical_device.name;

  //---------------------------
}
void Interface::fill_vulkan_device(prf::vulkan::Profiler* prf_vulkan){
  vector<prf::vulkan::Device>& vec_device = prf_vulkan->get_info_device();
  //---------------------------

  for(int i=0; i<vk_struct->instance.vec_physical_device.size(); i++){
    vk::structure::Physical_device& physical_device = vk_struct->instance.vec_physical_device[i];
    prf::vulkan::Device device_info;

    device_info.name = physical_device.name;
    device_info.has_extension_support = physical_device.has_extension_support;
    device_info.discrete_gpu = physical_device.discrete_gpu;
    device_info.max_image_dim = physical_device.max_image_dim;
    device_info.vendorID = physical_device.vendorID;

    for(int i=0; i<physical_device.vec_queue_family.size(); i++){
      prf::vulkan::Queue_family queue_family;
      queue_family.nb_queue = physical_device.vec_queue_family[i].nb_queue;
      queue_family.graphics = physical_device.vec_queue_family[i].capable_graphics;
      queue_family.compute = physical_device.vec_queue_family[i].capable_compute;
      queue_family.transfer = physical_device.vec_queue_family[i].capable_transfer;
      queue_family.sparseBinding = physical_device.vec_queue_family[i].capable_sparseBinding;
      queue_family.presentation = physical_device.vec_queue_family[i].capable_presentation;

      device_info.vec_queue_family.push_back(queue_family);
    }

    vec_device.push_back(device_info);
  }

  //---------------------------
}

//Subfunction
string Interface::get_gpu_name(){
  return vk_struct->device.physical_device.name;
}
vec4* Interface::get_color_background(){
  return &vk_struct->param.background_color;
}
bool Interface::is_gpu_discrete(){
  return vk_struct->device.physical_device.discrete_gpu;
}

}