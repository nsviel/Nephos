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

//Main function
void Info::fill_info(){
  prf::vulkan::Manager* prf_vulkan = struct_vulkan->prf_vulkan;
  //---------------------------

  vector<prf::vulkan::Device>& vec_device = prf_vulkan->get_info_device();

  prf::vulkan::Device device_info;
  device_info.name = struct_vulkan->device.physical_device.name;
  device_info.has_extension_support = struct_vulkan->device.physical_device.has_extension_support;
  device_info.max_image_dim = struct_vulkan->device.physical_device.max_image_dim;
  device_info.vendorID = struct_vulkan->device.physical_device.vendorID;

  device_info.queue_graphics_idx = struct_vulkan->device.physical_device.queue_graphics_idx;
  device_info.queue_transfer_idx = struct_vulkan->device.physical_device.queue_transfer_idx;
  device_info.queue_presentation_idx = struct_vulkan->device.physical_device.queue_presentation_idx;

  device_info.nb_queue_family = struct_vulkan->device.physical_device.nb_queue_family;
  device_info.nb_queue_graphics = struct_vulkan->device.physical_device.nb_queue_graphics;
  device_info.nb_queue_compute = struct_vulkan->device.physical_device.nb_queue_compute;
  device_info.nb_queue_transfer = struct_vulkan->device.physical_device.nb_queue_transfer;
  device_info.nb_queue_sparseBinding = struct_vulkan->device.physical_device.nb_queue_sparseBinding;
  device_info.nb_queue_presentation = struct_vulkan->device.physical_device.nb_queue_presentation;

  //---------------------------
}
string Info::get_gpu_name(){
  return struct_vulkan->device.physical_device.name;
}
vec4* Info::get_color_background(){
  return &struct_vulkan->param.background_color;
}


}
