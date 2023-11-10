#include "VK_device.h"

#include <VK_device/VK_physical_device.h>
#include <VK_main/VK_engine.h>
#include <VK_main/Struct_vulkan.h>


//Constructor / Destructor
VK_device::VK_device(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_physical_device = new VK_physical_device(struct_vulkan);

  //---------------------------
}
VK_device::~VK_device(){}

//Main functions
void VK_device::init(){
  //---------------------------

  vk_physical_device->init();
  this->create_logical_device();

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
  std::set<uint32_t> set_queue = {
    (unsigned int)struct_vulkan->device.struct_device.queue_graphics_idx,
    (unsigned int)struct_vulkan->device.struct_device.queue_presentation_idx
  };

  //Create queue on device
  float queuePriority = 1.0f;
  std::vector<VkDeviceQueueCreateInfo> queue_create_info;
  for(uint32_t queueFamily : set_queue){
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queue_create_info.push_back(queueCreateInfo);
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
  create_info.enabledExtensionCount = static_cast<uint32_t>(struct_vulkan->instance.extension_khr.size());
  create_info.ppEnabledExtensionNames = struct_vulkan->instance.extension_khr.data();
  create_info.enabledLayerCount = 0;

  //Creating the logical device
  VkResult result = vkCreateDevice(struct_vulkan->device.struct_device.physical_device, &create_info, nullptr, &struct_vulkan->device.device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create logical device!");
  }

  //Get queue family handles
  vkGetDeviceQueue(struct_vulkan->device.device, struct_vulkan->device.struct_device.queue_graphics_idx, 0, &struct_vulkan->device.queue_graphics);
  vkGetDeviceQueue(struct_vulkan->device.device, struct_vulkan->device.struct_device.queue_presentation_idx, 0, &struct_vulkan->device.queue_presentation);

  //---------------------------
}
