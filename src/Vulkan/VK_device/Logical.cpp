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

  struct_vulkan->profiler->prf_vulkan->add_queue(prf::vulkan::GRAPHICS, 0);
  struct_vulkan->profiler->prf_vulkan->add_queue(prf::vulkan::PRESENTATION, 0);
  struct_vulkan->profiler->prf_vulkan->add_queue(prf::vulkan::TRANSFER, 2);

  struct_vulkan->device.queue.graphics.ID_family = 0;
  struct_vulkan->device.queue.presentation.ID_family = 0;
  struct_vulkan->device.queue.transfer.ID_family = 0;

  //Set of required queues
  std::set<int> set_queue = {
    struct_vulkan->device.queue.graphics.ID_family,
    struct_vulkan->device.queue.presentation.ID_family,
    struct_vulkan->device.queue.transfer.ID_family
  };

  //Create queue on device
  float queuePriority[3] = {1.0f, 1.0f, 1.0f};
  vector<VkDeviceQueueCreateInfo> vec_queue_info;
  for(int queue_family : set_queue){
    if(queue_family == -1) continue;

    VkDeviceQueueCreateInfo queue_info{};
    queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.queueFamilyIndex = static_cast<uint32_t>(queue_family);
    queue_info.queueCount = 3;
    queue_info.pQueuePriorities = queuePriority;

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
  if(queue_graphics.ID_family != -1){
    vkGetDeviceQueue(struct_vulkan->device.handle, queue_graphics.ID_family, 0, &queue_graphics.ID);
  }

  //Presentation
  vk::structure::Queue& queue_presentation = struct_vulkan->device.queue.presentation;
  if(queue_presentation.ID_family != -1){
    vkGetDeviceQueue(struct_vulkan->device.handle, queue_presentation.ID_family, 1, &queue_presentation.ID);
  }

  //Transfer
  vk::structure::Queue& queue_transfer = struct_vulkan->device.queue.transfer;
  if(queue_transfer.ID_family != -1){
    vkGetDeviceQueue(struct_vulkan->device.handle, queue_transfer.ID_family, 2, &queue_transfer.ID);
  }

  //---------------------------
}

}
