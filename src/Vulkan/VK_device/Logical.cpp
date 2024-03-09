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
  vk_dev_queue->find_queue_family_assigment();
  this->create_logical_device();
  this->create_device_queue();

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
  vk_dev_queue->create_queue_info(vec_queue_info);

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
void Logical::create_device_queue(){
  vk::structure::queue::Pool& pool = struct_vulkan->device.queue;
  //---------------------------

  vk_dev_queue->create_queue(pool.graphics);
  vk_dev_queue->create_queue(pool.presentation);
  vk_dev_queue->create_queue(pool.transfer);

  //---------------------------
}




}
