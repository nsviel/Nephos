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

  //---------------------------
}
Collector::~Collector(){}

//Profiler vulkan info
void Collector::collect_info(){
  //---------------------------

  this->collect_gpu_info();
  this->collect_vulkan_device();
  this->collect_vulkan_queue();

  //---------------------------
}

//Subfunction
void Collector::collect_gpu_info(){
  //---------------------------

  prf_struct->hardware.gpu.temperature = utl_nvidia->get_temperature();
  prf_struct->hardware.gpu.total_consumption = utl_nvidia->get_total_consumption();
  prf_struct->hardware.gpu.fan_speed = utl_nvidia->get_fan_speed();
  prf_struct->hardware.gpu.power_usage = utl_nvidia->get_power_usage();

  //---------------------------
}
void Collector::collect_vulkan_device(){
  //---------------------------

  for(int i=0; i<vk_struct->instance.vec_physical_device.size(); i++){
    vk::device::structure::Physical& physical_device = vk_struct->instance.vec_physical_device[i];

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
      prf_struct->hardware.gpu.name = physical_device.name;
    }

    prf_struct->hardware.vec_device.push_back(device_info);
  }

  //---------------------------
}
void Collector::collect_vulkan_queue(){
  //---------------------------

  this->add_queue(vk_struct->device.queue.graphics, prf::hardware::queue::GRAPHICS);
  this->add_queue(vk_struct->device.queue.presentation, prf::hardware::queue::PRESENTATION);
  this->add_queue(vk_struct->device.queue.transfer, prf::hardware::queue::TRANSFER);

  //---------------------------
}
void Collector::add_queue(vk::queue::structure::Queue& queue, int type){
  //---------------------------

  prf::hardware::Queue prf_queue;
  prf_queue.type = (prf::hardware::queue::Type)type;
  prf_queue.number++;
  prf_queue.family_ID = queue.family_ID;
  prf_queue.thread_ID = queue.thread_ID;
  prf_struct->hardware.gpu.vec_queue.push_back(prf_queue);

  //---------------------------
}


}
