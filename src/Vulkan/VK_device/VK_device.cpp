#include "VK_device.h"

#include <Vulkan/Namespace.h>


namespace vk::device{

//Constructor / Destructor
VK_device::VK_device(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_physical_device = new vk::device::VK_physical_device(struct_vulkan);

  //---------------------------
}
VK_device::~VK_device(){}

//Main functions
void VK_device::init(){
  //---------------------------

  vk_physical_device->init();
  this->create_logical_device();
  this->find_device_queue_handles();

  //---------------------------
}
void VK_device::clean(){
  //---------------------------

  vkDestroyDevice(struct_vulkan->device.device, nullptr);

  //---------------------------
}

//Subfunction
void VK_device::create_logical_device(){
  //---------------------------

  //Get GPU queue families
  std::set<int> set_queue = {
    struct_vulkan->device.physical_device.queue_graphics_idx,
    struct_vulkan->device.physical_device.queue_presentation_idx
  };

  //Create queue on device
  float queuePriority = 1.0f;
  vector<VkDeviceQueueCreateInfo> queue_create_info;
  for(int queue_family : set_queue){
    if(queue_family != -1){
      VkDeviceQueueCreateInfo queueCreateInfo{};
      queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      queueCreateInfo.queueFamilyIndex = static_cast<uint32_t>(queue_family);
      queueCreateInfo.queueCount = 1;
      queueCreateInfo.pQueuePriorities = &queuePriority;
      queue_create_info.push_back(queueCreateInfo);
    }
  }

  //Specifying used device features
  VkPhysicalDeviceFeatures device_features{};
  device_features.samplerAnisotropy = VK_TRUE;
  device_features.wideLines = VK_TRUE;

  //Logical device info
  VkDeviceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  create_info.pQueueCreateInfos = queue_create_info.data();
  create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_info.size());
  create_info.pEnabledFeatures = &device_features;
  create_info.enabledExtensionCount = static_cast<uint32_t>(struct_vulkan->instance.extension_device.size());
  create_info.ppEnabledExtensionNames = struct_vulkan->instance.extension_device.data();
  create_info.enabledLayerCount = 0;

  //Creating the logical device
  VkResult result = vkCreateDevice(struct_vulkan->device.physical_device.physical_device, &create_info, nullptr, &struct_vulkan->device.device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create logical device!");
  }

  //---------------------------
}
void VK_device::find_device_queue_handles(){
  //---------------------------

  int& queue_graphics = struct_vulkan->device.physical_device.queue_graphics_idx;
  if(queue_graphics != -1){
    vkGetDeviceQueue(struct_vulkan->device.device, queue_graphics, 0, &struct_vulkan->device.queue_graphics);
  }

  int& queue_presentation = struct_vulkan->device.physical_device.queue_presentation_idx;
  if(queue_presentation != -1){
    vkGetDeviceQueue(struct_vulkan->device.device, queue_presentation, 0, &struct_vulkan->device.queue_presentation);
  }

  //---------------------------
}

}
