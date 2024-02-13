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
  prf::vulkan::Manager* prf_vulkan = struct_vulkan->prf_vulkan;
  //---------------------------

  this->fill_vulkan_info(prf_vulkan);
  this->fill_vulkan_device(prf_vulkan);

  //---------------------------
}
void Info::fill_vulkan_info(prf::vulkan::Manager* prf_vulkan){
  prf::vulkan::Info* info_vulkan = prf_vulkan->get_info_vulkan();
  //---------------------------

  info_vulkan->selected_gpu = struct_vulkan->device.physical_device.name;

  //---------------------------
}
void Info::fill_vulkan_device(prf::vulkan::Manager* prf_vulkan){
  vector<prf::vulkan::Device>& vec_device = prf_vulkan->get_info_device();
  //---------------------------

  for(int i=0; i<struct_vulkan->instance.vec_physical_device.size(); i++){
    vk::structure::Physical_device& physical_device = struct_vulkan->instance.vec_physical_device[i];
    prf::vulkan::Device device_info;

    device_info.name = physical_device.name;
    device_info.has_extension_support = physical_device.has_extension_support;
    device_info.max_image_dim = physical_device.max_image_dim;
    device_info.vendorID = physical_device.vendorID;

    device_info.queue_graphics_idx = physical_device.queue_graphics_idx;
    device_info.queue_transfer_idx = physical_device.queue_transfer_idx;
    device_info.queue_presentation_idx = physical_device.queue_presentation_idx;

    device_info.nb_queue_family = physical_device.nb_queue_family;
    device_info.nb_queue_graphics = physical_device.nb_queue_graphics;
    device_info.nb_queue_compute = physical_device.nb_queue_compute;
    device_info.nb_queue_transfer = physical_device.nb_queue_transfer;
    device_info.nb_queue_sparseBinding = physical_device.nb_queue_sparseBinding;
    device_info.nb_queue_presentation = physical_device.nb_queue_presentation;

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


}
