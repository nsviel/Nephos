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
void Queue::find_queue_nb_family(vk::structure::Physical_device& physical_device){
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
  uint32_t nb_queue_graphics = 0;
  uint32_t nb_queue_compute = 0;
  uint32_t nb_queue_transfer = 0;
  uint32_t nb_queue_sparseBinding = 0;
  uint32_t nb_queue_presentation = 0;

  for (uint32_t i = 0; i < nb_queue_family; ++i) {
    nb_queue_graphics += (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) ? queue_families[i].queueCount : 0;
    nb_queue_compute += (queue_families[i].queueFlags & VK_QUEUE_COMPUTE_BIT) ? queue_families[i].queueCount : 0;
    nb_queue_transfer += (queue_families[i].queueFlags & VK_QUEUE_TRANSFER_BIT) ? queue_families[i].queueCount : 0;
    nb_queue_sparseBinding += (queue_families[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) ? queue_families[i].queueCount : 0;

    if(struct_vulkan->param.headless == false){
      VkBool32 presentSupport = false;
      vkGetPhysicalDeviceSurfaceSupportKHR(physical_device.handle, i, struct_vulkan->window.surface, &presentSupport);
      if(presentSupport){
        nb_queue_presentation += queue_families[i].queueCount;
      }
    }
  }

  physical_device.nb_queue_family = nb_queue_family;
  physical_device.nb_queue_graphics = nb_queue_graphics;
  physical_device.nb_queue_compute = nb_queue_compute;
  physical_device.nb_queue_transfer = nb_queue_transfer;
  physical_device.nb_queue_sparseBinding = nb_queue_sparseBinding;
  physical_device.nb_queue_presentation = nb_queue_presentation;

  //---------------------------
}
void Queue::find_queue_graphics_idx(vk::structure::Physical_device& physical_device){
  //---------------------------

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(physical_device.nb_queue_family );
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &physical_device.nb_queue_family , vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  for(int i=0; i<vec_queueFamily.size(); i++){
    const auto& queueFamily = vec_queueFamily[i];

    //Querying for graphics family
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
      physical_device.queue_family_graphics_idx = static_cast<uint32_t>(i);
      return;
    }
  }

  //---------------------------
}
void Queue::find_queue_transfer_idx(vk::structure::Physical_device& physical_device){
  //---------------------------

  // List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(physical_device.nb_queue_family);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &physical_device.nb_queue_family, vec_queueFamily.data());

  // Search for specific properties (e.g., transfer)
  for(int i=0; i<vec_queueFamily.size(); i++){
    const auto& queueFamily = vec_queueFamily[i];

    // Querying for transfer family
    if(queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT){
      physical_device.queue_family_transfer_idx = static_cast<uint32_t>(i);
      return;
    }
  }

  //---------------------------
}
void Queue::find_queue_presentation_idx(vk::structure::Physical_device& physical_device){
  //---------------------------

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(physical_device.nb_queue_family );
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &physical_device.nb_queue_family , vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  for(int i=0; i<vec_queueFamily.size(); i++){
    const auto& queueFamily = vec_queueFamily[i];

    //Querying for presentation family
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(physical_device.handle, static_cast<uint32_t>(i), struct_vulkan->window.surface, &presentSupport);
    if(presentSupport){
      physical_device.queue_family_presentation_idx = static_cast<uint32_t>(i);
      return;
    }
  }

  //---------------------------
}

}
