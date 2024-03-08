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
    vk::structure::Queue_family queue_family;
    queue_family.property = queue_families[i];
    queue_family.nb_queue_graphics = (queue_family.property.queueFlags & VK_QUEUE_GRAPHICS_BIT) ? queue_family.property.queueCount : 0;
    queue_family.nb_queue_compute = (queue_family.property.queueFlags & VK_QUEUE_COMPUTE_BIT) ? queue_family.property.queueCount : 0;
    queue_family.nb_queue_transfer = (queue_family.property.queueFlags & VK_QUEUE_TRANSFER_BIT) ? queue_family.property.queueCount : 0;
    queue_family.nb_queue_sparseBinding = (queue_family.property.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) ? queue_family.property.queueCount : 0;

    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(physical_device.handle, i, struct_vulkan->window.surface, &presentSupport);
    if(presentSupport){
      queue_family.nb_queue_presentation = queue_family.property.queueCount;
    }

    physical_device.vec_queue_family.push_back(queue_family);
  }

  //---------------------------
}
void Queue::find_queue_graphics_idx(vk::structure::Physical_device& physical_device){
  //---------------------------

  for(int i=0; i<physical_device.vec_queue_family.size(); i++){
    vk::structure::Queue_family& queue_family = physical_device.vec_queue_family[i];

    //Querying for graphics family
    if(queue_family.nb_queue_graphics > 0){
      physical_device.queue_family_graphics_idx = i;
      return;
    }
  }

  //---------------------------
}
void Queue::find_queue_transfer_idx(vk::structure::Physical_device& physical_device){
  //---------------------------

  for(int i=0; i<physical_device.vec_queue_family.size(); i++){
    vk::structure::Queue_family& queue_family = physical_device.vec_queue_family[i];

    // Querying for transfer family
    if(queue_family.nb_queue_transfer > 0){
      physical_device.queue_family_transfer_idx = i;
      return;
    }
  }

  //---------------------------
}
void Queue::find_queue_presentation_idx(vk::structure::Physical_device& physical_device){
  //---------------------------

  for(int i=0; i<physical_device.vec_queue_family.size(); i++){
    vk::structure::Queue_family& queue_family = physical_device.vec_queue_family[i];

    //Querying for presentation family
    if(queue_family.nb_queue_presentation > 0){
      physical_device.queue_family_presentation_idx = i;
      return;
    }
  }

  //---------------------------
}

//Subfunction
bool Queue::is_physical_device_queue_suitable(vk::structure::Physical_device& physical_device){
  //---------------------------

  if(physical_device.queue_family_graphics_idx == -1) return false;
  if(physical_device.queue_family_transfer_idx == -1) return false;
  if(physical_device.queue_family_presentation_idx == -1) return false;

  //---------------------------
  return true;
}


}
