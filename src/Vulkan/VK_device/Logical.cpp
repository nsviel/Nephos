#include "Logical.h"

#include <Vulkan/Namespace.h>


namespace vk::device{

//Constructor / Destructor
Logical::Logical(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->dev_physical = new vk::device::Physical(struct_vulkan);

  //---------------------------
}
Logical::~Logical(){}

//Main functions
void Logical::init(){
  //---------------------------

  dev_physical->init();
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

  //Get GPU queue families
  std::set<int> set_queue = {
    struct_vulkan->device.physical_device.queue_family_graphics_idx,
    struct_vulkan->device.physical_device.queue_family_transfer_idx,
    struct_vulkan->device.physical_device.queue_family_presentation_idx
  };

  //Create queue on device
  float queuePriority[3] = {1.0f, 1.0f, 1.0f};
  vector<VkDeviceQueueCreateInfo> vec_queue_info;
  for(int queue_family : set_queue){
    if(queue_family != -1){
      VkDeviceQueueCreateInfo queue_info{};
      queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      queue_info.queueFamilyIndex = static_cast<uint32_t>(queue_family);
      queue_info.queueCount = 3;
      queue_info.pQueuePriorities = queuePriority;
      vec_queue_info.push_back(queue_info);
    }
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
void Logical::find_device_queue(){
  //---------------------------

  //Graphics
  int& queue_family_graphics = struct_vulkan->device.physical_device.queue_family_graphics_idx;
  if(queue_family_graphics != -1){
    vkGetDeviceQueue(struct_vulkan->device.handle, queue_family_graphics, 0, &struct_vulkan->device.queue.graphics);
  }

  //Presentation
  int& queue_family_presentation = struct_vulkan->device.physical_device.queue_family_presentation_idx;
  if(queue_family_presentation != -1){
    vkGetDeviceQueue(struct_vulkan->device.handle, queue_family_presentation, 1, &struct_vulkan->device.queue.presentation);
  }

  //Transfer
  int& queue_family_transfer = struct_vulkan->device.physical_device.queue_family_transfer_idx;
  if(queue_family_transfer != -1){
    vkGetDeviceQueue(struct_vulkan->device.handle, queue_family_transfer, 2, &struct_vulkan->device.queue.transfer);
  }

  //---------------------------
}

}
