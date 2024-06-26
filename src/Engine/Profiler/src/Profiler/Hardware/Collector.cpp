#include "Collector.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::hardware{

//Constructor / Destructor
Collector::Collector(prf::hardware::Structure* prf_struct){
  //---------------------------

  this->prf_struct = prf_struct;

  //---------------------------
}
Collector::~Collector(){}

//Profiler vulkan info
void Collector::collect_info(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->collect_vulkan_device(vk_struct);

  //---------------------------
}

//Subfunction
void Collector::collect_vulkan_device(vk::structure::Vulkan* vk_struct){
  //---------------------------

  for(int i=0; i<vk_struct->instance.vec_physical_device.size(); i++){
    vk::structure::Physical_device& physical_device = vk_struct->instance.vec_physical_device[i];

    //Device info
    prf::hardware::Device device_info;
    device_info.name = physical_device.name;
    device_info.has_extension_support = physical_device.has_extension_support;
    device_info.discrete_gpu = physical_device.discrete_gpu;
    device_info.max_image_dim = physical_device.max_image_dim;
    device_info.vendor_ID = physical_device.vendor_ID;

    //Gather device queue info
    for(int i=0; i<physical_device.vec_queue_family.size(); i++){
      prf::hardware::queue::Family queue_family;
      queue_family.nb_queue = physical_device.vec_queue_family[i].nb_queue;
      queue_family.graphics = physical_device.vec_queue_family[i].capable_graphics;
      queue_family.compute = physical_device.vec_queue_family[i].capable_compute;
      queue_family.transfer = physical_device.vec_queue_family[i].capable_transfer;
      queue_family.sparseBinding = physical_device.vec_queue_family[i].capable_sparseBinding;
      queue_family.presentation = physical_device.vec_queue_family[i].capable_presentation;

      device_info.vec_queue_family.push_back(queue_family);
    }

    //Check if it is the selected one
    if(physical_device.name == vk_struct->device.physical_device.name){
      prf_struct->selected_device = device_info;
    }

    prf_struct->vec_device.push_back(device_info);
  }

  //---------------------------
}

}
