#include "VK_swapchain.h"
#include "VK_frame.h"
#include <VK_main/VK_engine.h>
#include "../VK_struct/struct_vulkan.h"
#include <VK_drawing/VK_viewport.h>
#include "../VK_presentation/VK_framebuffer.h"
#include "../VK_image/VK_depth.h"
#include "../VK_device/VK_physical_device.h"

#include <ELE_window/Window.h>


//Constructor / Destructor
VK_swapchain::VK_swapchain(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->window = vk_engine->get_window();
  this->vk_physical_device = vk_engine->get_vk_physical_device();
  this->vk_depth = new VK_depth(vk_engine);

  //---------------------------
}
VK_swapchain::~VK_swapchain(){}

//Swap chain function
void VK_swapchain::recreate_swapChain(){
  VK_frame* vk_frame = vk_engine->get_vk_frame();
  //---------------------------

  //Minimization managment
  int width = 0, height = 0;
  while(width == 0 || height == 0){
    glfwGetFramebufferSize(window->get_window(), &width, &height);
    glfwWaitEvents();
  }

  vkDeviceWaitIdle(struct_vulkan->device.device);

  //Clean old values
  vk_frame->clean_frame_swapchain(&struct_vulkan->swapchain);
  vk_frame->clean_frame_renderpass(&struct_vulkan->renderpass_scene);
  vk_frame->clean_frame_renderpass(&struct_vulkan->renderpass_edl);
  this->clean_swapchain();

  //Recreate values
  this->create_swapchain();
  vk_frame->create_frame_swapchain(&struct_vulkan->swapchain);
  vk_frame->create_frame_renderpass(&struct_vulkan->renderpass_scene);
  vk_frame->create_frame_renderpass(&struct_vulkan->renderpass_edl);

  //---------------------------
}
void VK_swapchain::clean_swapchain(){
  //---------------------------

  vkDestroySwapchainKHR(struct_vulkan->device.device, struct_vulkan->swapchain.swapchain, nullptr);

  VK_frame* vk_frame = vk_engine->get_vk_frame();
  vk_frame->clean_frame_swapchain(&struct_vulkan->swapchain);

  //---------------------------
}

//Swap chain creation
void VK_swapchain::create_swapchain(){
  VK_viewport* vk_viewport = vk_engine->get_vk_viewport();
  //---------------------------

  //Create swap chain info
  VkSwapchainCreateInfoKHR createInfo{};
  this->create_swapchain_surface(createInfo);
  this->create_swapchain_family(createInfo);
  this->create_swapchain_presentation(createInfo);

  //Create swap chain
  VkResult result = vkCreateSwapchainKHR(struct_vulkan->device.device, &createInfo, nullptr, &struct_vulkan->swapchain.swapchain);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create swap chain!");
  }

  this->create_swapchain_image(struct_vulkan->swapchain.swapchain, createInfo.minImageCount);
  vk_viewport->update_viewport();

  //---------------------------
}
void VK_swapchain::create_swapchain_surface(VkSwapchainCreateInfoKHR& createInfo){
  //---------------------------

  VkSurfaceCapabilitiesKHR surface_capability = vk_physical_device->find_surface_capability(struct_vulkan->device.physical_device);
  vector<VkSurfaceFormatKHR> surface_format = vk_physical_device->find_surface_format(struct_vulkan->device.physical_device);
  VkSurfaceFormatKHR surfaceFormat = swapchain_surface_format(surface_format);
  vk_physical_device->compute_extent();

  //Get swap chain image capacity (0 means no maximum)
  uint32_t nb_image = surface_capability.minImageCount + 1;
  if(surface_capability.maxImageCount > 0 && nb_image > surface_capability.maxImageCount){
    nb_image = surface_capability.maxImageCount;
  }
  struct_vulkan->nb_frame = nb_image;

  createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  createInfo.minImageCount = nb_image;
  createInfo.surface = struct_vulkan->window.surface;
  createInfo.imageFormat = surfaceFormat.format;
  createInfo.imageColorSpace = surfaceFormat.colorSpace;
  createInfo.imageExtent = struct_vulkan->window.extent;
  createInfo.imageArrayLayers = 1;
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //VK_IMAGE_USAGE_TRANSFER_DST_BIT for post-processing

  createInfo.preTransform = surface_capability.currentTransform;

  //---------------------------
}
void VK_swapchain::create_swapchain_family(VkSwapchainCreateInfoKHR& createInfo){
  //---------------------------

  //Link with queue families
  int family_graphics = vk_physical_device->find_queue_family_graphics(struct_vulkan->device.physical_device);
  int family_presentation = vk_physical_device->find_queue_family_presentation(struct_vulkan->device.physical_device);
  uint32_t queueFamilyIndices[] = {(unsigned int)family_graphics, (unsigned int)family_presentation};

  if(family_graphics != family_presentation){
    createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount = 2;
    createInfo.pQueueFamilyIndices = queueFamilyIndices;
  }else{
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0; // Optional
    createInfo.pQueueFamilyIndices = nullptr; // Optional
  }

  //---------------------------
}
void VK_swapchain::create_swapchain_presentation(VkSwapchainCreateInfoKHR& createInfo){
  //---------------------------

  vector<VkPresentModeKHR> dev_presentation_mode = vk_physical_device->find_presentation_mode(struct_vulkan->device.physical_device);
  VkPresentModeKHR presentation_mode = swapchain_presentation_mode(dev_presentation_mode);

  createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //Ignore alpha channel
  createInfo.presentMode = presentation_mode;
  createInfo.clipped = VK_TRUE;
  createInfo.oldSwapchain = VK_NULL_HANDLE;

  //---------------------------
}
void VK_swapchain::create_swapchain_image(VkSwapchainKHR swapchain, unsigned int min_image_count){
  //---------------------------

  //For swapchain image we use vkGetSwapchainImagesKHR instead of VkImageCreateInfo
  //to get the correct image which are managed by the presentation engine

  //Empty swapchain image
  vkGetSwapchainImagesKHR(struct_vulkan->device.device, swapchain, &min_image_count, nullptr);

  //Fill swapchain image
  struct_vulkan->swapchain.vec_swapchain_image.resize(min_image_count);
  vkGetSwapchainImagesKHR(struct_vulkan->device.device, swapchain, &min_image_count, struct_vulkan->swapchain.vec_swapchain_image.data());

  //---------------------------
}

//Swap chain parameter
VkSurfaceFormatKHR VK_swapchain::swapchain_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format){
  //---------------------------

  //Check if standar RGB is available
  for(const auto& format : dev_format){
    if(format.format == struct_vulkan->required_image_format && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
      return format;
    }
  }

  //---------------------------
  return dev_format[0];
}
VkPresentModeKHR VK_swapchain::swapchain_presentation_mode(const std::vector<VkPresentModeKHR>& dev_mode){
  //4 possible modes:
  //- VK_PRESENT_MODE_IMMEDIATE_KHR
  //- VK_PRESENT_MODE_FIFO_KHR
  //- VK_PRESENT_MODE_FIFO_RELAXED_KHR
  //- VK_PRESENT_MODE_MAILBOX_KHR
  //---------------------------

  //Check for VK_PRESENT_MODE_MAILBOX_KHR mode
  for(const auto& mode : dev_mode){
    if(mode == VK_PRESENT_MODE_MAILBOX_KHR){
      return mode;
    }
  }

  //---------------------------
  return VK_PRESENT_MODE_FIFO_KHR;
}
