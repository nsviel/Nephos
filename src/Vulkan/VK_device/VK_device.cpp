#include "VK_device.h"
#include "VK_physical_device.h"

#include <VK_main/VK_engine.h>
#include "../VK_struct/Struct_vulkan.h"


//Constructor / Destructor
VK_device::VK_device(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_physical_device = new VK_physical_device(vk_engine);

  //---------------------------
}
VK_device::~VK_device(){}

//Main functions
void VK_device::init_device(){
  //---------------------------

  vk_physical_device->init_physical_device();
  this->create_logical_device();

  //---------------------------
}
void VK_device::clean_device(){
  //---------------------------

  vkDestroyDevice(struct_vulkan->device.device, nullptr);

  //---------------------------
}

//Subfunction
void VK_device::create_logical_device(){
  //Interface between selected GPU and application
  //---------------------------

  //Get GPU queue families
  int family_graphics = vk_physical_device->find_queue_family_graphics(struct_vulkan->device.physical_device);
  int family_presentation = vk_physical_device->find_queue_family_presentation(struct_vulkan->device.physical_device);
  std::set<uint32_t> uniqueQueueFamilies = {(unsigned int)family_graphics, (unsigned int)family_presentation};

  //Create queue on device
  float queuePriority = 1.0f;
  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  for(uint32_t queueFamily : uniqueQueueFamilies){
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queueCreateInfos.push_back(queueCreateInfo);
  }

  //Specifying used device features
  VkPhysicalDeviceFeatures deviceFeatures{};
  deviceFeatures.samplerAnisotropy = VK_TRUE;
  deviceFeatures.wideLines = VK_TRUE;

  //Logical device info
  VkDeviceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  createInfo.pQueueCreateInfos = queueCreateInfos.data();
  createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
  createInfo.pEnabledFeatures = &deviceFeatures;
  createInfo.enabledExtensionCount = static_cast<uint32_t>(struct_vulkan->device.extension.size());
  createInfo.ppEnabledExtensionNames = struct_vulkan->device.extension.data();
  createInfo.enabledLayerCount = 0;

  //Creating the logical device
  VkResult result = vkCreateDevice(struct_vulkan->device.physical_device, &createInfo, nullptr, &struct_vulkan->device.device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create logical device!");
  }

  //Get queue family handles
  vkGetDeviceQueue(struct_vulkan->device.device, family_graphics, 0, &struct_vulkan->device.queue_graphics);
  vkGetDeviceQueue(struct_vulkan->device.device, family_presentation, 0, &struct_vulkan->device.queue_presentation);

  //---------------------------
}
