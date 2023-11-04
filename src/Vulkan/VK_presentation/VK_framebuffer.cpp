#include "VK_framebuffer.h"

#include <VK_main/VK_engine.h>
#include "../VK_struct/struct_vulkan.h"
#include "../VK_presentation/VK_swapchain.h"
#include "../VK_presentation/VK_frame.h"
#include "../VK_image/VK_depth.h"
#include "../VK_device/VK_device.h"
#include "../VK_renderpass/VK_renderpass.h"


//Constructor / Destructor
VK_framebuffer::VK_framebuffer(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();

  //---------------------------
}
VK_framebuffer::~VK_framebuffer(){}

//FBO creation
void VK_framebuffer::create_framebuffer(Struct_renderpass* renderpass, Frame* image){
  //---------------------------

  //Create frambuffer
  vector<VkImageView> attachments;
  attachments.push_back(image->color.view);
  attachments.push_back(image->depth.view);

  VkFramebufferCreateInfo framebufferInfo{};
  framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  framebufferInfo.renderPass = renderpass->renderpass;
  framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
  framebufferInfo.pAttachments = attachments.data();
  framebufferInfo.width = struct_vulkan->window.extent.width;
  framebufferInfo.height = struct_vulkan->window.extent.height;
  framebufferInfo.layers = 1;

  VkFramebuffer fbo;
  VkResult result = vkCreateFramebuffer(struct_vulkan->device.device, &framebufferInfo, nullptr, &fbo);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create framebuffer!");
  }

  //---------------------------
  image->fbo = fbo;
}

//Deletion function
void VK_framebuffer::clean_framebuffer(Frame* image){
  //---------------------------

  vkDestroyFramebuffer(struct_vulkan->device.device, image->fbo, nullptr);

  //---------------------------
}
