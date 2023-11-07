#include "VK_framebuffer.h"

#include <VK_main/VK_engine.h>
#include <VK_struct/Struct_vulkan.h>
#include <VK_presentation/VK_swapchain.h>
#include <VK_presentation/VK_frame.h>
#include <VK_image/VK_depth.h>
#include <VK_device/VK_device.h>
#include <VK_image/VK_color.h>
#include <VK_image/VK_image.h>
#include <VK_renderpass/VK_renderpass.h>


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
  fbo->color.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  fbo->color.layout = IMAGE_LAYOUT_SHADER_READONLY;
  fbo->depth.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  fbo->depth.layout = IMAGE_LAYOUT_DEPTH_READONLY;

  vk_color->create_color_attachment(&fbo->color);
  vk_depth->create_depth_attachment(&fbo->depth);
  this->create_framebuffer_renderpass(renderpass, fbo);

  renderpass->framebuffer = fbo;

  //---------------------------
}
void VK_framebuffer::clean_framebuffer(Struct_renderpass* renderpass){
  Struct_framebuffer* fbo = renderpass->framebuffer;
  //---------------------------

  vk_image->clean_image(&fbo->color);
  vk_image->clean_image(&fbo->depth);
  this->clean_framebuffer_obj(fbo);
  delete fbo;

  //---------------------------
}

//Subfunction
void VK_framebuffer::create_framebuffer_renderpass(Struct_renderpass* renderpass, Struct_framebuffer* framebuffer){
  //---------------------------

  //Create frambuffer
  vector<VkImageView> attachments;
  attachments.push_back(framebuffer->color.view);
  attachments.push_back(framebuffer->depth.view);

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
  framebuffer->fbo = fbo;
}
void VK_framebuffer::create_framebuffer_swapchain(Struct_renderpass* renderpass, Struct_frame* frame){
  //---------------------------

  //Create frambuffer
  vector<VkImageView> attachments;
  attachments.push_back(frame->image.view);

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
  frame->framebuffer = fbo;
}
void VK_framebuffer::clean_framebuffer_obj(Struct_framebuffer* framebuffer){
  //---------------------------

  vkDestroyFramebuffer(struct_vulkan->device.device, framebuffer->fbo, nullptr);

  //---------------------------
}
