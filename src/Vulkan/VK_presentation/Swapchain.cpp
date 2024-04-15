#include "Swapchain.h"

#include <Vulkan/Namespace.h>


namespace vk::presentation{

//Constructor / Destructor
Swapchain::Swapchain(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->dev_physical = new vk::device::Physical(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_frame = new vk::presentation::Frame(vk_struct);
  this->vk_framebuffer = new vk::renderpass::Framebuffer(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);
  this->vk_window = new vk::window::GLFW(vk_struct);

  //---------------------------
}
Swapchain::~Swapchain(){}

//Swap chain function
void Swapchain::create_swapchain(){
  //---------------------------

  dev_physical->compute_extent();
  this->find_swapchain_surface_format();
  this->find_swapchain_max_nb_image();
  this->find_swapchain_presentation_mode();
  this->create_swapchain_handle();
  this->create_swapchain_image();
  vk_viewport->update_viewport();

  //---------------------------
}
void Swapchain::recreate_swapchain(){
  //---------------------------

  //Pause if window is minimized
  vec2 dim = vk_window->update_window_dim();
  while(dim == vec2(0, 0)){
    vk_window->wait_event();
  }

  //Clean old swapchain
  vk_synchro->wait_idle();
  vk_framebuffer->clean_framebuffers();
  this->clean();

  //Create new swapchain
  this->create_swapchain();
  vk_frame->create_frame();
  vk_framebuffer->create_framebuffers();
  vk_synchro->end_idle();

  //---------------------------
}
void Swapchain::clean(){
  //---------------------------

  vkDestroySwapchainKHR(vk_struct->device.handle, vk_struct->swapchain.swapchain, nullptr);
  vk_frame->clean_frame();

  //---------------------------
}

//Swap chain creation
void Swapchain::create_swapchain_image(){
  //---------------------------

  //For swapchain image we use vkGetSwapchainImagesKHR instead of VkImageCreateInfo
  //to get the correct image which are managed by the presentation engine

  //Empty swapchain image
  vkGetSwapchainImagesKHR(vk_struct->device.handle, vk_struct->swapchain.swapchain, &vk_struct->swapchain.max_nb_frame, nullptr);

  //Fill swapchain image
  vk_struct->swapchain.vec_swapchain_image.resize(vk_struct->swapchain.max_nb_frame);
  vkGetSwapchainImagesKHR(vk_struct->device.handle, vk_struct->swapchain.swapchain, &vk_struct->swapchain.max_nb_frame, vk_struct->swapchain.vec_swapchain_image.data());

  //---------------------------
}
void Swapchain::create_swapchain_handle(){
  if(vk_struct->param.headless) return;
  //---------------------------

  uint32_t queueFamilyIndices[] = {
    (unsigned int) vk_struct->device.queue.graphics.family_ID,
    (unsigned int) vk_struct->device.queue.presentation.family_ID
  };

  VkSwapchainCreateInfoKHR create_info{};
  if(vk_struct->device.queue.graphics.family_ID != vk_struct->device.queue.presentation.family_ID){
    create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    create_info.queueFamilyIndexCount = 2;
    create_info.pQueueFamilyIndices = queueFamilyIndices;
  }else{
    create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    create_info.queueFamilyIndexCount = 0; // Optional
    create_info.pQueueFamilyIndices = nullptr; // Optional
  }

  create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  create_info.minImageCount = vk_struct->swapchain.max_nb_frame;
  create_info.surface = vk_struct->window.surface;
  create_info.imageFormat = vk_struct->swapchain.format.format;
  create_info.imageColorSpace = vk_struct->swapchain.format.colorSpace;
  create_info.imageExtent = vk_struct->window.extent;
  create_info.imageArrayLayers = 1;
  create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //VK_IMAGE_USAGE_TRANSFER_DST_BIT for post-processing
  create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //Ignore alpha channel
  create_info.presentMode = vk_struct->swapchain.presentation_mode;
  create_info.clipped = VK_TRUE;
  create_info.oldSwapchain = VK_NULL_HANDLE;

  VkSurfaceCapabilitiesKHR surface_capability = vk_struct->device.physical_device.capabilities;
  create_info.preTransform = surface_capability.currentTransform;

  VkResult result = vkCreateSwapchainKHR(vk_struct->device.handle, &create_info, nullptr, &vk_struct->swapchain.swapchain);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create swap chain!");
  }

  //---------------------------
}
void Swapchain::find_swapchain_max_nb_image(){
  VkSurfaceCapabilitiesKHR surface_capability = vk_struct->device.physical_device.capabilities;
  //---------------------------

  //Get swap chain image capacity (0 means no maximum)
  uint32_t nb_image = surface_capability.minImageCount + 1;
  if(surface_capability.maxImageCount > 0 && nb_image > surface_capability.maxImageCount){
    nb_image = surface_capability.maxImageCount;
  }

  //---------------------------
  vk_struct->swapchain.max_nb_frame = nb_image;
}
void Swapchain::find_swapchain_surface_format(){
  vector<VkSurfaceFormatKHR>& dev_format = vk_struct->device.physical_device.formats;
  VkSurfaceFormatKHR swapchain_format = dev_format[0];
  //---------------------------

  //Check if standar RGB is available
  for(const auto& format : dev_format){
    if(format.format == vk_struct->render.required_image_format && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
      swapchain_format = format;
      break;
    }
  }

  //---------------------------
  vk_struct->swapchain.format = swapchain_format;
}
void Swapchain::find_swapchain_presentation_mode(){
  vector<VkPresentModeKHR>& dev_mode = vk_struct->device.physical_device.presentation_mode;
  //---------------------------

  //4 possible modes:
  //- VK_PRESENT_MODE_IMMEDIATE_KHR -> no VSync
  //- VK_PRESENT_MODE_FIFO_KHR -> VSync + VBI
  //- VK_PRESENT_MODE_FIFO_RELAXED_KHR -> VSync
  //- VK_PRESENT_MODE_MAILBOX_KHR -> VSync + triple buffering
  VkPresentModeKHR presentation_mode = VK_PRESENT_MODE_FIFO_KHR;
  for(const auto& mode : dev_mode){
    if(mode == VK_PRESENT_MODE_IMMEDIATE_KHR){
      presentation_mode = mode;
    }
  }

  //---------------------------
  vk_struct->swapchain.presentation_mode = presentation_mode;
}

}
