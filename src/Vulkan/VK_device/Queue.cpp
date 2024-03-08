#include "Queue.h"

#include <Vulkan/Namespace.h>


namespace vk::device{

//Constructor / Destructor
Queue::Queue(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Queue::~Queue(){}

//Main functions
void Queue::find_queue_family_composition(vk::structure::Physical_device& physical_device){
  //---------------------------

  uint32_t nb_queue_family = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &nb_queue_family, nullptr);
  if(nb_queue_family == 0) {
    throw std::runtime_error("[error] No queue families on selected GPU");
  }

  // Retrieve information about each queue family
  vector<VkQueueFamilyProperties> queue_families(nb_queue_family);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &nb_queue_family, queue_families.data());

  // Count the number of each type of queue
  for(uint32_t i=0; i<nb_queue_family; ++i){
    vk::structure::queue::family queue_family;
    queue_family.property = queue_families[i];
    queue_family.nb_queue = queue_family.property.queueCount;
    queue_family.graphics = (queue_family.property.queueFlags & VK_QUEUE_GRAPHICS_BIT) ? true : false;
    queue_family.compute = (queue_family.property.queueFlags & VK_QUEUE_COMPUTE_BIT) ? true : false;
    queue_family.transfer = (queue_family.property.queueFlags & VK_QUEUE_TRANSFER_BIT) ? true : false;
    queue_family.sparseBinding = (queue_family.property.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) ? true : false;

    VkBool32 presentation_supported = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(physical_device.handle, i, struct_vulkan->window.surface, &presentation_supported);
    queue_family.presentation = presentation_supported;

    physical_device.vec_queue_family.push_back(queue_family);
  }

  //---------------------------
}
bool Queue::suitability_for_presentation(vk::structure::Physical_device& physical_device){
  //---------------------------

  bool is_device_suitable = false;
  bool is_graphics_able = false;
  bool is_transfer_able = false;

  for(int i=0; i<physical_device.vec_queue_family.size(); i++){
    vk::structure::queue::family& queue_family = physical_device.vec_queue_family[i];

    //Querying for graphics family
    if(queue_family.graphics && queue_family.presentation){
      is_graphics_able = true;
    }

    //Querying for transfer family
    if(queue_family.transfer){
      is_transfer_able = true;
    }
  }

  if(is_graphics_able && is_transfer_able){
    is_device_suitable = true;
  }

  //---------------------------
  return is_device_suitable;
}
bool Queue::suitability_for_graphics(vk::structure::Physical_device& physical_device){
  //---------------------------

  bool is_device_suitable = false;
  bool is_graphics_able = false;
  bool is_transfer_able = false;

  for(int i=0; i<physical_device.vec_queue_family.size(); i++){
    vk::structure::queue::family& queue_family = physical_device.vec_queue_family[i];

    //Querying for graphics family
    if(queue_family.graphics){
      is_graphics_able = true;
    }

    //Querying for transfer family
    if(queue_family.transfer){
      is_transfer_able = true;
    }
  }

  if(is_graphics_able && is_transfer_able){
    is_device_suitable = true;
  }

  //---------------------------
  return is_device_suitable;
}

}
