#include "VK_framebuffer.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_image/VK_depth.h>
#include <VK_image/VK_color.h>
#include <VK_image/VK_image.h>


//Constructor / Destructor
VK_framebuffer::VK_framebuffer(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_color = new VK_color(struct_vulkan);
  this->vk_depth = new VK_depth(struct_vulkan);
  this->vk_image = new VK_image(struct_vulkan);

  //---------------------------
}
VK_framebuffer::~VK_framebuffer(){}

//FBO creation
void VK_framebuffer::create_framebuffers(){
  //---------------------------

  for(int i=0; i<struct_vulkan->render.vec_renderpass.size(); i++){
    Struct_vk_renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];
    this->create_framebuffer(renderpass);
  }

  //---------------------------
}
void VK_framebuffer::create_framebuffer(Struct_vk_renderpass* renderpass){
  //---------------------------

  Struct_vk_framebuffer* framebuffer = new Struct_vk_framebuffer();
  framebuffer->color.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  framebuffer->color.layout = TYP_IMAGE_LAYOUT_SHADER_READONLY;
  framebuffer->depth.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  framebuffer->depth.layout = TYP_IMAGE_LAYOUT_DEPTH_READONLY;

  vk_color->create_color_attachment(&framebuffer->color);
  vk_depth->create_depth_attachment(&framebuffer->depth);
  this->create_framebuffer_renderpass(renderpass, framebuffer);

  renderpass->framebuffer = framebuffer;

  //---------------------------
}
void VK_framebuffer::clean_framebuffers(){
  //---------------------------

  for(int i=0; i<struct_vulkan->render.vec_renderpass.size(); i++){
    Struct_vk_renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];
    this->clean_framebuffer(renderpass);
  }

  //---------------------------
}
void VK_framebuffer::clean_framebuffer(Struct_vk_renderpass* renderpass){
  Struct_vk_framebuffer* framebuffer = renderpass->framebuffer;
  //---------------------------

  vk_image->clean_image(&framebuffer->color);
  vk_image->clean_image(&framebuffer->depth);
  this->clean_framebuffer_obj(framebuffer->fbo);
  delete framebuffer;

  //---------------------------
}

//Subfunction
void VK_framebuffer::create_framebuffer_renderpass(Struct_vk_renderpass* renderpass, Struct_vk_framebuffer* framebuffer){
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
void VK_framebuffer::create_framebuffer_swapchain(Struct_vk_renderpass* renderpass, Struct_frame* frame){
  //---------------------------

  //Create frambuffer
  vector<VkImageView> attachments;
  attachments.push_back(frame->image.view);
  attachments.push_back(frame->depth.view);

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
  frame->fbo = fbo;
}
void VK_framebuffer::clean_framebuffer_obj(VkFramebuffer& fbo){
  //---------------------------

  vkDestroyFramebuffer(struct_vulkan->device.device, fbo, nullptr);

  //---------------------------
}
