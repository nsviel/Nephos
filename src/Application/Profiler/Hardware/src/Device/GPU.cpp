#include "GPU.h"

#include <Hardware/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace prf::hardware{

//Constructor / Destructor
GPU::GPU(prf::hardware::Node* node_hardware){
  //---------------------------

  vk::Node* node_vulkan = node_hardware->get_node_vulkan();

  this->vk_struct = node_vulkan->get_vk_struct();
  this->prf_struct = node_hardware->get_prf_struct();
  this->utl_nvidia = new sys::hardware::Nvidia();

  //---------------------------
}
GPU::~GPU(){}

//Main function

void GPU::collect_gpu_info(){
  //---------------------------

  prf_struct->gpu.temperature_max = utl_nvidia->get_temperature_max_shutdown();

  //---------------------------
}
void GPU::collect_gpu_variable(){
  //---------------------------

  prf_struct->gpu.temperature = utl_nvidia->get_temperature();
  prf_struct->gpu.total_consumption = utl_nvidia->get_total_consumption();
  prf_struct->gpu.fan_speed = utl_nvidia->get_fan_speed();
  prf_struct->gpu.power_usage = utl_nvidia->get_power_usage();

  //---------------------------
}
void GPU::collect_vulkan_info(){
  //---------------------------

  this->collect_vulkan_device();
  this->collect_vulkan_queue();

  //---------------------------
}

//Subfunction
void GPU::collect_vulkan_device(){
  //---------------------------

  for(int i=0; i<vk_struct->core.instance.vec_physical_device.size(); i++){
    vk::device::structure::Physical& physical_device = vk_struct->core.instance.vec_physical_device[i];

    //Device info
    prf::hardware::structure::Device device_info;
    device_info.name = physical_device.name;
    device_info.has_extension_support = physical_device.has_extension_support;
    device_info.discrete_gpu = physical_device.discrete_gpu;
    device_info.max_image_dim = physical_device.max_image_dim;
    device_info.vendor_ID = physical_device.vendor_ID;

    //Gather device queue info
    for(int i=0; i<physical_device.vec_queue_family.size(); i++){
      prf::hardware::structure::queue::Family queue_family;
      queue_family.nb_queue = physical_device.vec_queue_family[i].nb_queue;
      queue_family.graphics = physical_device.vec_queue_family[i].capable_graphics;
      queue_family.compute = physical_device.vec_queue_family[i].capable_compute;
      queue_family.transfer = physical_device.vec_queue_family[i].capable_transfer;
      queue_family.sparseBinding = physical_device.vec_queue_family[i].capable_sparseBinding;
      queue_family.presentation = physical_device.vec_queue_family[i].capable_presentation;

      device_info.vec_queue_family.push_back(queue_family);
    }

    //Check if it is the selected one
    if(physical_device.name == vk_struct->core.device.physical_device.name){
      prf_struct->gpu.name = physical_device.name;
    }

    prf_struct->vec_device.push_back(device_info);
  }

  //---------------------------
}
void GPU::collect_vulkan_queue(){
  //---------------------------

  this->add_queue(vk_struct->core.device.queue.graphics, prf::hardware::structure::queue::GRAPHICS);
  this->add_queue(vk_struct->core.device.queue.presentation, prf::hardware::structure::queue::PRESENTATION);
  this->add_queue(vk_struct->core.device.queue.transfer, prf::hardware::structure::queue::TRANSFER);

  //---------------------------
}
void GPU::add_queue(vk::queue::structure::Queue& queue, int type){
  //---------------------------

  prf::hardware::structure::Queue prf_queue;
  prf_queue.type = (prf::hardware::structure::queue::Type)type;
  prf_queue.number++;
  prf_queue.family_ID = queue.family_ID;
  prf_queue.family_idx = queue.family_index;
  prf_queue.thread_ID = queue.thread_ID;
  prf_struct->gpu.vec_queue.push_back(prf_queue);

  //---------------------------
}

}
