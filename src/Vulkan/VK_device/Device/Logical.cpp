#include "Logical.h"

#include <Vulkan/Namespace.h>


namespace vk::device{

//Constructor / Destructor
Logical::Logical(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_dev_physical = new vk::device::Physical(vk_struct);
  this->vk_queue = new vk::device::queue::Manager(vk_struct);

  //---------------------------
}
Logical::~Logical(){}

//Main function
void Logical::init(){
  //---------------------------

  vk_dev_physical->find_physical_device();
  this->create_logical_device();
  this->create_device_queue();

  //---------------------------
}
void Logical::clean(){
  //---------------------------

  vkDestroyDevice(vk_struct->device.handle, nullptr);
  vk_struct->device.handle = VK_NULL_HANDLE;

  //---------------------------
}

//Subfunction
void Logical::create_logical_device(){
  //---------------------------

  std::vector<VkDeviceQueueCreateInfo> vec_queue_info;
  vk_queue->create_queue_info(vec_queue_info);

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
  create_info.enabledExtensionCount = static_cast<uint32_t>(vk_struct->instance.extension_device.size());
  create_info.ppEnabledExtensionNames = vk_struct->instance.extension_device.data();
  create_info.enabledLayerCount = 0;

  //Creating the logical device
  VkResult result = vkCreateDevice(vk_struct->device.physical_device.handle, &create_info, nullptr, &vk_struct->device.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create logical device!");
  }

  //---------------------------
}
void Logical::create_device_queue(){
  vk::queue::structure::Set& set = vk_struct->device.queue;
  //---------------------------

  vk_queue->create_queue(set.graphics);
  vk_queue->create_queue(set.presentation);
  vk_queue->create_queue(set.transfer);

  //---------------------------
}




}
