#include "Logical.h"

#include <Vulkan/Namespace.h>


namespace vk::device{

//Constructor / Destructor
Logical::Logical(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_dev_physical = new vk::device::Physical(struct_vulkan);
  this->vk_dev_queue = new vk::device::Queue(struct_vulkan);

  //---------------------------
}
Logical::~Logical(){}

//Main functions
void Logical::init(){
  //---------------------------

  vk_dev_physical->find_physical_device();
  vk_dev_queue->assign_queue_family();
  this->create_logical_device();
  this->find_device_queue();

  //---------------------------
}
void Logical::clean(){
  //---------------------------

  vkDestroyDevice(struct_vulkan->device.handle, nullptr);
  struct_vulkan->device.handle = VK_NULL_HANDLE;

  //---------------------------
}

//Subfunction
void Logical::create_logical_device(){
  //---------------------------

  vector<VkDeviceQueueCreateInfo> vec_queue_info;
  std::vector<vk::structure::queue::Family>& vec_queue_family = struct_vulkan->device.physical_device.vec_queue_family;
  for(int i=0; i<vec_queue_family.size(); i++){
    vk::structure::queue::Family& family = vec_queue_family[i];
    if(family.nb_queue_required == 0) continue;

    family.vec_queue_priority = vector<float>(family.nb_queue_required, 1.0f);

    VkDeviceQueueCreateInfo queue_info{};
    queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.queueFamilyIndex = static_cast<uint32_t>(family.ID);
    queue_info.queueCount = family.nb_queue_required;
    queue_info.pQueuePriorities = family.vec_queue_priority.data();

    vec_queue_info.push_back(queue_info);
  }

  //Specifying used device features
  VkPhysicalDeviceFeatures device_features{};
  device_features.samplerAnisotropy = VK_TRUE;
  device_features.wideLines = VK_TRUE;

  //Logical device info
  VkDeviceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  create_info.pQueueCreateInfos = vec_queue_info.data();
  create_info.queueCreateInfoCount = static_cast<uint32_t>(vec_queue_info.size());
  create_info.pEnabledFeatures = &device_features;
  create_info.enabledExtensionCount = static_cast<uint32_t>(struct_vulkan->instance.extension_device.size());
  create_info.ppEnabledExtensionNames = struct_vulkan->instance.extension_device.data();
  create_info.enabledLayerCount = 0;

  //Creating the logical device
  VkResult result = vkCreateDevice(struct_vulkan->device.physical_device.handle, &create_info, nullptr, &struct_vulkan->device.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create logical device!");
  }

  //---------------------------
}

//Queue stuff
void Logical::find_device_queue(){
  //---------------------------

  //Graphics
  vk::structure::Queue& queue_graphics = struct_vulkan->device.queue.graphics;
  if(queue_graphics.family_ID != -1){
    vkGetDeviceQueue(struct_vulkan->device.handle, queue_graphics.family_ID, 0, &queue_graphics.handle);
  }

  //Presentation
  vk::structure::Queue& queue_presentation = struct_vulkan->device.queue.presentation;
  if(queue_presentation.family_ID != -1){
    vkGetDeviceQueue(struct_vulkan->device.handle, queue_presentation.family_ID, 1, &queue_presentation.handle);
  }

  //Transfer
  vk::structure::Queue& queue_transfer = struct_vulkan->device.queue.transfer;
  if(queue_transfer.family_ID != -1){
    vkGetDeviceQueue(struct_vulkan->device.handle, queue_transfer.family_ID, 2, &queue_transfer.handle);
  }

  //---------------------------
}

}
