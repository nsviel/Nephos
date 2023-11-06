#include "VK_framebuffer.h"

#include <VK_main/VK_engine.h>
#include "../VK_struct/Struct_vulkan.h"
#include "../VK_presentation/VK_swapchain.h"
#include "../VK_presentation/VK_frame.h"
#include "../VK_image/VK_depth.h"
#include "../VK_device/VK_device.h"
#include "../VK_image/VK_color.h"
#include "../VK_image/VK_image.h"
#include "../VK_drawing/VK_renderpass.h"


//Constructor / Destructor
VK_framebuffer::VK_framebuffer(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_color = new VK_color(vk_engine);
  this->vk_depth = new VK_depth(vk_engine);
  this->vk_image = new VK_image(vk_engine);

  //---------------------------
}
VK_framebuffer::~VK_framebuffer(){}

//FBO creation
void VK_framebuffer::create_framebuffer(Struct_renderpass* renderpass){
  //---------------------------

  Struct_framebuffer* fbo = new Struct_framebuffer();
  fbo->color.usage = renderpass->color_image_usage;
  fbo->color.layout = renderpass->color_sampler_layout;
  fbo->depth.usage = renderpass->depth_image_usage;
  fbo->depth.layout = renderpass->depth_sampler_layout;

  vk_color->create_color_attachment(fbo);
  vk_depth->create_depth_attachment(fbo);
  this->create_framebuffer_obj(renderpass, fbo);

  renderpass->framebuffer = fbo;

  //---------------------------
}
void VK_framebuffer::clean_frame_renderpass(Struct_renderpass* renderpass){
  Struct_framebuffer* fbo = renderpass->framebuffer;
  //---------------------------

  vk_image->clean_image(&fbo->color);
  vk_image->clean_image(&fbo->depth);
  this->clean_framebuffer_obj(fbo);
  delete fbo;

  //---------------------------
}



//Subfunction
void VK_framebuffer::create_framebuffer_obj(Struct_renderpass* renderpass, Struct_framebuffer* image){
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
void VK_framebuffer::clean_framebuffer_obj(Struct_framebuffer* image){
  //---------------------------

  vkDestroyFramebuffer(struct_vulkan->device.device, image->fbo, nullptr);

  //---------------------------
}
