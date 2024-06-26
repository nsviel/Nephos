#include "Collector.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::vulkan{

//Constructor / Destructor
Collector::Collector(prf::vulkan::Info* prf_info){
  //---------------------------

  this->prf_info = prf_info;

  //---------------------------
}
Collector::~Collector(){}

//Profiler vulkan info
void Collector::collect_info(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->collect_vulkan_info(vk_struct);
  this->collect_vulkan_device(vk_struct);

  //---------------------------
}

//Subfunction
void Collector::collect_vulkan_info(vk::structure::Vulkan* vk_struct){
  //---------------------------

  prf_info->selected_gpu = vk_struct->device.physical_device.name;

  //---------------------------
}
void Collector::collect_vulkan_device(vk::structure::Vulkan* vk_struct){
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

    this->vec_device.push_back(device_info);
  }

  //---------------------------
}

}
