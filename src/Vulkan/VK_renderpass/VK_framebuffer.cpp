#include "VK_framebuffer.h"

#include <Vulkan/Namespace.h>


//Constructor / Destructor
VK_framebuffer::VK_framebuffer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_color = new vk::image::Color(struct_vulkan);
  this->vk_depth = new vk::image::Depth(struct_vulkan);
  this->vk_image = new vk::image::Image(struct_vulkan);

  //---------------------------
}
VK_framebuffer::~VK_framebuffer(){}

//FBO creation
void VK_framebuffer::create_framebuffers(){
  //---------------------------

  for(int i=0; i<struct_vulkan->render.vec_renderpass.size(); i++){
    vk::structure::Renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];
    this->create_framebuffer(renderpass);
  }

  //---------------------------
}
void VK_framebuffer::create_framebuffer(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Framebuffer* framebuffer = new vk::structure::Framebuffer();
  framebuffer->color.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  framebuffer->color.layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  framebuffer->depth.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  framebuffer->depth.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

  vk_depth->create_depth_image(&framebuffer->depth);
  vk_color->create_color_image(&framebuffer->color);
  vk_color->create_color_image(&framebuffer->color_resolve);
  this->create_framebuffer_renderpass(renderpass, framebuffer);

  renderpass->framebuffer = framebuffer;

  //---------------------------
}
void VK_framebuffer::clean_framebuffers(){
  //---------------------------

  for(int i=0; i<struct_vulkan->render.vec_renderpass.size(); i++){
    vk::structure::Renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];
    this->clean_framebuffer(renderpass);
  }

  //---------------------------
}
void VK_framebuffer::clean_framebuffer(vk::structure::Renderpass* renderpass){
  vk::structure::Framebuffer* framebuffer = renderpass->framebuffer;
  //---------------------------

  vk_image->clean_image(&framebuffer->color);
  vk_image->clean_image(&framebuffer->color_resolve);
  vk_image->clean_image(&framebuffer->depth);
  this->clean_framebuffer_obj(framebuffer->fbo);
  delete framebuffer;

  //---------------------------
}

//Subfunction
void VK_framebuffer::create_framebuffer_renderpass(vk::structure::Renderpass* renderpass, vk::structure::Framebuffer* framebuffer){
  //---------------------------

  //Create frambuffer
  vector<VkImageView> attachments;
  attachments.push_back(framebuffer->color.view);
  attachments.push_back(framebuffer->depth.view);

  //attachments.push_back(framebuffer->color_resolve.view);

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
void VK_framebuffer::create_framebuffer_swapchain(vk::structure::Renderpass* renderpass, vk::structure::Frame* frame){
  //---------------------------

  //Create frambuffer
  vector<VkImageView> attachments;

  attachments.push_back(frame->color.view);
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
