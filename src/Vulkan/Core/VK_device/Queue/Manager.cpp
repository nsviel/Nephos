#include "Manager.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <set>


namespace vk::device::queue{

//Constructor / Destructor
Manager::Manager(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_assigment = new vk::device::queue::Assignment(vk_struct);

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::create_queue(vk::structure::Queue& queue){
  if(queue.family_ID == -1) return;
  //---------------------------

  vkGetDeviceQueue(vk_struct->core.device.handle, queue.family_ID, queue.family_index, &queue.handle);

  //---------------------------
}
void Manager::create_queue_info(std::vector<VkDeviceQueueCreateInfo>& vec_queue_info){
  //---------------------------

  vk_assigment->assign_queue();

  for(auto& family : vk_struct->core.device.physical_device.vec_queue_family){
    if(family.vec_queue.size() == 0) continue;

    //Create queue info accordingly
    VkDeviceQueueCreateInfo queue_info{};
    queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.queueFamilyIndex = static_cast<uint32_t>(family.ID);
    queue_info.queueCount = family.vec_queue.size();
    queue_info.pQueuePriorities = family.vec_priority.data();

    vec_queue_info.push_back(queue_info);
  }

  //---------------------------
}

//Subfunction
void Manager::find_queue_family_composition(vk::structure::Physical& physical_device){
  //---------------------------

  uint32_t nb_queue_family = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &nb_queue_family, nullptr);
  if(nb_queue_family == 0){
    throw std::runtime_error("[error] No queue families on selected GPU");
  }

  // Retrieve information about each queue family
  std::vector<VkQueueFamilyProperties> queue_families(nb_queue_family);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &nb_queue_family, queue_families.data());

  // Count the number of each type of queue
  for(int i=0; i<nb_queue_family; i++){
    //Queue family properties
    vk::structure::Queue_family queue_family;
    queue_family.ID = i;
    queue_family.property = queue_families[i];
    queue_family.nb_queue = queue_family.property.queueCount;
    queue_family.capable_graphics = (queue_family.property.queueFlags & VK_QUEUE_GRAPHICS_BIT) ? true : false;
    queue_family.capable_compute = (queue_family.property.queueFlags & VK_QUEUE_COMPUTE_BIT) ? true : false;
    queue_family.capable_transfer = (queue_family.property.queueFlags & VK_QUEUE_TRANSFER_BIT) ? true : false;
    queue_family.capable_sparseBinding = (queue_family.property.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) ? true : false;

    //Presentation property
    if(!vk_struct->interface.param.headless){
      VkBool32 presentation_supported = false;
      vkGetPhysicalDeviceSurfaceSupportKHR(physical_device.handle, i, vk_struct->window.surface, &presentation_supported);
      queue_family.capable_presentation = presentation_supported;
    }

    physical_device.vec_queue_family.push_back(queue_family);
  }

  //---------------------------
}
bool Manager::suitability_for_presentation(vk::structure::Physical& physical_device){
  //---------------------------

  bool is_device_suitable = false;
  bool is_graphics_able = false;
  bool is_transfer_able = false;

  for(auto& queue_family : physical_device.vec_queue_family){
    //Querying for graphics family
    if(queue_family.capable_graphics && queue_family.capable_presentation){
      is_graphics_able = true;
    }

    //Querying for transfer family
    if(queue_family.capable_transfer){
      is_transfer_able = true;
    }
  }

  if(is_graphics_able && is_transfer_able){
    is_device_suitable = true;
  }

  //---------------------------
  return is_device_suitable;
}
bool Manager::suitability_for_graphics(vk::structure::Physical& physical_device){
  //---------------------------

  bool is_device_suitable = false;
  bool is_graphics_able = false;
  bool is_transfer_able = false;

  for(auto& queue_family : physical_device.vec_queue_family){
    //Querying for graphics family
    if(queue_family.capable_graphics){
      is_graphics_able = true;
    }

    //Querying for transfer family
    if(queue_family.capable_transfer){
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
