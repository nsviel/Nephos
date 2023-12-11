#include "VK_swapchain.h"

#include <VK_struct/Namespace.h>
#include <VK_render/VK_frame.h>
#include <VK_drawing/VK_viewport.h>
#include <VK_struct/Namespace.h>
#include <VK_render/VK_framebuffer.h>
#include <VK_render/VK_surface.h>
#include <VK_device/VK_physical_device.h>


//Constructor / Destructor
VK_swapchain::VK_swapchain(vk::structure::Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_physical_device = new VK_physical_device(struct_vulkan);
  this->vk_viewport = new VK_viewport(struct_vulkan);
  this->vk_frame = new VK_frame(struct_vulkan);
  this->vk_framebuffer = new VK_framebuffer(struct_vulkan);
  this->vk_surface = new VK_surface(struct_vulkan);

  //---------------------------
}
VK_swapchain::~VK_swapchain(){}

//Swap chain function
void VK_swapchain::create_swapchain(){
  //---------------------------

  vk_physical_device->compute_extent();
  this->find_swapchain_surface_format();
  this->find_swapchain_max_nb_image();
  this->find_swapchain_presentation_mode();
  this->create_swapchain_obj();
  this->create_swapchain_image();
  vk_viewport->update_viewport();

  //---------------------------
}
void VK_swapchain::recreate_swapchain(){
  //---------------------------

  //Minimization managment
  int width = 0, height = 0;
  while(width == 0 || height == 0){
    glfwGetFramebufferSize(struct_vulkan->window.glfw_window, &width, &height);
    glfwWaitEvents();
  }

  vkDeviceWaitIdle(struct_vulkan->device.device);

  //Clean old swapchain
  vk_framebuffer->clean_framebuffers();
  this->clean_swapchain();

  //Create new swapchain
  this->create_swapchain();
  vk_frame->create_frame();
  vk_framebuffer->create_framebuffers();

  //---------------------------
}
void VK_swapchain::clean_swapchain(){
  //---------------------------

  vkDestroySwapchainKHR(struct_vulkan->device.device, struct_vulkan->swapchain.swapchain, nullptr);
  vk_frame->clean_frame();

  //---------------------------
}

//Swap chain creation
void VK_swapchain::create_swapchain_image(){
  //---------------------------

  //For swapchain image we use vkGetSwapchainImagesKHR instead of VkImageCreateInfo
  //to get the correct image which are managed by the presentation engine

  //Empty swapchain image
  vkGetSwapchainImagesKHR(struct_vulkan->device.device, struct_vulkan->swapchain.swapchain, &struct_vulkan->swapchain.max_nb_frame, nullptr);

  //Fill swapchain image
  struct_vulkan->swapchain.vec_swapchain_image.resize(struct_vulkan->swapchain.max_nb_frame);
  vkGetSwapchainImagesKHR(struct_vulkan->device.device, struct_vulkan->swapchain.swapchain, &struct_vulkan->swapchain.max_nb_frame, struct_vulkan->swapchain.vec_swapchain_image.data());

  //---------------------------
}
void VK_swapchain::create_swapchain_obj(){
  //---------------------------

  uint32_t queueFamilyIndices[] = {
    (unsigned int) struct_vulkan->device.struct_device.queue_graphics_idx,
    (unsigned int) struct_vulkan->device.struct_device.queue_presentation_idx
  };

  VkSwapchainCreateInfoKHR create_info{};
  if(struct_vulkan->device.struct_device.queue_graphics_idx != struct_vulkan->device.struct_device.queue_presentation_idx){
    create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    create_info.queueFamilyIndexCount = 2;
    create_info.pQueueFamilyIndices = queueFamilyIndices;
  }else{
    create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    create_info.queueFamilyIndexCount = 0; // Optional
    create_info.pQueueFamilyIndices = nullptr; // Optional
  }

  create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  create_info.minImageCount = struct_vulkan->swapchain.max_nb_frame;
  create_info.surface = struct_vulkan->window.surface;
  create_info.imageFormat = struct_vulkan->swapchain.format.format;
  create_info.imageColorSpace = struct_vulkan->swapchain.format.colorSpace;
  create_info.imageExtent = struct_vulkan->window.extent;
  create_info.imageArrayLayers = 1;
  create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //VK_IMAGE_USAGE_TRANSFER_DST_BIT for post-processing
  create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //Ignore alpha channel
  create_info.presentMode = struct_vulkan->swapchain.presentation_mode;
  create_info.clipped = VK_TRUE;
  create_info.oldSwapchain = VK_NULL_HANDLE;

  VkSurfaceCapabilitiesKHR surface_capability = struct_vulkan->device.struct_device.capabilities;
  create_info.preTransform = surface_capability.currentTransform;

  VkResult result = vkCreateSwapchainKHR(struct_vulkan->device.device, &create_info, nullptr, &struct_vulkan->swapchain.swapchain);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create swap chain!");
  }

  //---------------------------
}
void VK_swapchain::find_swapchain_max_nb_image(){
  VkSurfaceCapabilitiesKHR surface_capability = struct_vulkan->device.struct_device.capabilities;
  //---------------------------

  //Get swap chain image capacity (0 means no maximum)
  uint32_t nb_image = surface_capability.minImageCount + 1;
  if(surface_capability.maxImageCount > 0 && nb_image > surface_capability.maxImageCount){
    nb_image = surface_capability.maxImageCount;
  }

  //---------------------------
  struct_vulkan->swapchain.max_nb_frame = nb_image;
}
void VK_swapchain::find_swapchain_surface_format(){
  vector<VkSurfaceFormatKHR>& dev_format = struct_vulkan->device.struct_device.formats;
  VkSurfaceFormatKHR swapchain_format = dev_format[0];
  //---------------------------

  //Check if standar RGB is available
  for(const auto& format : dev_format){
    if(format.format == struct_vulkan->render.required_image_format && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
      swapchain_format = format;
      break;
    }
  }

  //---------------------------
  struct_vulkan->swapchain.format = swapchain_format;
}
void VK_swapchain::find_swapchain_presentation_mode(){
  vector<VkPresentModeKHR>& dev_mode = struct_vulkan->device.struct_device.presentation_mode;
  //---------------------------

  //4 possible modes:
  //- VK_PRESENT_MODE_IMMEDIATE_KHR
  //- VK_PRESENT_MODE_FIFO_KHR
  //- VK_PRESENT_MODE_FIFO_RELAXED_KHR
  //- VK_PRESENT_MODE_MAILBOX_KHR
  VkPresentModeKHR presentation_mode = VK_PRESENT_MODE_FIFO_KHR;
  for(const auto& mode : dev_mode){
    if(mode == VK_PRESENT_MODE_MAILBOX_KHR){
      presentation_mode = mode;
    }
  }

  //---------------------------
  struct_vulkan->swapchain.presentation_mode = presentation_mode;
}
