#include "Swapchain.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::presentation{

//Constructor / Destructor
Swapchain::Swapchain(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->dev_physical = new vk::device::Physical(vk_struct);
  this->vk_viewport = new vk::draw::Viewport(vk_struct);
  this->vk_frame = new vk::presentation::Frame(vk_struct);
  this->vk_framebuffer = new vk::renderpass::Framebuffer(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_synchro = new vk::synchro::Synchro(vk_struct);
  this->vk_window = new vk::window::Window(vk_struct);
  this->vk_event = new vk::window::Event(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->vk_renderpass = new vk::renderpass::Renderpass(vk_struct);

  //---------------------------
}
Swapchain::~Swapchain(){}

//Main function
void Swapchain::init(){
  //---------------------------

  dev_physical->compute_extent();
  this->find_swapchain_surface_format();
  this->find_swapchain_max_nb_image();
  this->find_swapchain_presentation_mode();
  this->create_swapchain_handle();
  this->retrieve_swapchain_image();
  vk_viewport->update_viewport();
  vk_frame->create_frame();

  //---------------------------
}
void Swapchain::clean(){
  //---------------------------

  vk_frame->clean_frame();
  vkDestroySwapchainKHR(vk_struct->core.device.handle, vk_struct->core.swapchain.handle, nullptr);

  //---------------------------
}

//Swapchain function
void Swapchain::recreate_swapchain(){
  //---------------------------

  //Pause if window is minimized
  glm::vec2 dim = vk_struct->window.dimension;
  while(dim == glm::vec2(0, 0)){
    vk_event->wait_event();
  }

  //Clean old swapchain
  vk_window->update_window_dim();
  vk_synchro->wait_idle_and_pause();
  vk_framebuffer->clean();
  this->clean();

  //Create new swapchain
  this->init();
  vk_framebuffer->init();
  vk_synchro->end_idle();
  vk_imgui->resize_event();
  vk_semaphore->reset_pool();
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  vk_renderpass->actualize_sampler();

  //---------------------------
}
void Swapchain::retrieve_swapchain_image(){
  //---------------------------

  //Get number of swapchain images
  vkGetSwapchainImagesKHR(vk_struct->core.device.handle, vk_struct->core.swapchain.handle, &vk_struct->core.swapchain.max_frame, nullptr);

  //Fill swapchain image
  vk_struct->core.swapchain.vec_image.resize(vk_struct->core.swapchain.max_frame);
  vkGetSwapchainImagesKHR(vk_struct->core.device.handle, vk_struct->core.swapchain.handle, &vk_struct->core.swapchain.max_frame, vk_struct->core.swapchain.vec_image.data());

  //---------------------------
}
void Swapchain::create_swapchain_handle(){
  if(vk_struct->interface.param.headless) return;
  //---------------------------

  uint32_t queueFamilyIndices[] = {
    (unsigned int) vk_struct->core.device.queue.graphics.family_ID,
    (unsigned int) vk_struct->core.device.queue.presentation.family_ID
  };

  VkSwapchainCreateInfoKHR create_info{};
  if(vk_struct->core.device.queue.graphics.family_ID != vk_struct->core.device.queue.presentation.family_ID){
    create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    create_info.queueFamilyIndexCount = 2;
    create_info.pQueueFamilyIndices = queueFamilyIndices;
  }else{
    create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    create_info.queueFamilyIndexCount = 0; // Optional
    create_info.pQueueFamilyIndices = nullptr; // Optional
  }

  create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  create_info.minImageCount = vk_struct->core.swapchain.max_frame;
  create_info.surface = vk_struct->window.surface;
  create_info.imageFormat = vk_struct->core.swapchain.format.format;
  create_info.imageColorSpace = vk_struct->core.swapchain.format.colorSpace;
  create_info.imageExtent = vk_struct->window.extent;
  create_info.imageArrayLayers = 1;
  create_info.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //VK_IMAGE_USAGE_TRANSFER_DST_BIT for post-processing
  create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //Ignore alpha channel
  create_info.presentMode = vk_struct->core.swapchain.presentation_mode;
  create_info.clipped = VK_TRUE;
  create_info.oldSwapchain = VK_NULL_HANDLE;

  VkSurfaceCapabilitiesKHR surface_capability = vk_struct->core.device.physical_device.capabilities;
  create_info.preTransform = surface_capability.currentTransform;

  VkResult result = vkCreateSwapchainKHR(vk_struct->core.device.handle, &create_info, nullptr, &vk_struct->core.swapchain.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create swap chain!");
  }

  //---------------------------
}
void Swapchain::find_swapchain_max_nb_image(){
  VkSurfaceCapabilitiesKHR surface_capability = vk_struct->core.device.physical_device.capabilities;
  //---------------------------

  //Get swap chain image capacity (0 means no maximum)
  uint32_t nb_image = surface_capability.minImageCount + 1;
  if(surface_capability.maxImageCount > 0 && nb_image > surface_capability.maxImageCount){
    nb_image = surface_capability.maxImageCount;
  }

  //---------------------------
  vk_struct->core.swapchain.max_frame = nb_image;
}
void Swapchain::find_swapchain_surface_format(){
  std::vector<VkSurfaceFormatKHR>& vec_surface_format = vk_struct->core.device.physical_device.vec_surface_format;
  VkSurfaceFormatKHR swapchain_format = vec_surface_format[0];
  //---------------------------

  //Check if standar RGB is available
  for(const auto& format : vec_surface_format){
    if(format.format == vk_struct->core.swapchain.required_image_format && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
      swapchain_format = format;
      break;
    }
  }

  //---------------------------
  vk_struct->core.swapchain.format = swapchain_format;
}
void Swapchain::find_swapchain_presentation_mode(){
  std::vector<VkPresentModeKHR>& dev_mode = vk_struct->core.device.physical_device.presentation_mode;
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
  vk_struct->core.swapchain.presentation_mode = presentation_mode;
}
void Swapchain::next_frame_ID(){
  vk::structure::Swapchain& swapchain = vk_struct->core.swapchain;
  //---------------------------

  int current_ID = swapchain.current_ID;
  current_ID = (current_ID + 1) % vk_struct->core.instance.max_frame_inflight;
  swapchain.current_ID = current_ID;

  //---------------------------
}

}
