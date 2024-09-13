#include "Framebuffer.h"

#include <Vulkan/Namespace.h>


namespace vk::renderpass{

//Constructor / Destructor
Framebuffer::Framebuffer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_color = new vk::image::Color(vk_struct);
  this->vk_depth = new vk::image::Depth(vk_struct);
  this->vk_image = new vk::image::Image(vk_struct);

  //---------------------------
}
Framebuffer::~Framebuffer(){}

//Main function
void Framebuffer::init(){
  //---------------------------

  for(auto& renderpass : vk_struct->renderpass.vector){
    this->create_framebuffer(*renderpass);
  }

  //---------------------------
}
void Framebuffer::clean(){
  //---------------------------

  for(auto& renderpass : vk_struct->renderpass.vector){
    this->clean_framebuffer(*renderpass);
  }

  //---------------------------
}

//Creation function
void Framebuffer::create_framebuffer(vk::structure::Renderpass& renderpass){
  //---------------------------

  vk::structure::Framebuffer& framebuffer = renderpass.framebuffer;
  framebuffer.color.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  framebuffer.color.layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  framebuffer.depth.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  framebuffer.depth.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

  this->create_framebuffer_image(framebuffer);
  this->create_framebuffer_handle(renderpass, framebuffer);

  //---------------------------
}
void Framebuffer::clean_framebuffer(vk::structure::Renderpass& renderpass){
  vk::structure::Framebuffer& framebuffer = renderpass.framebuffer;
  //---------------------------

  this->clean_framebuffer_image(framebuffer);
  this->clean_framebuffer_handle(framebuffer.handle);

  //---------------------------
}

//Subfunction
void Framebuffer::create_framebuffer_image(vk::structure::Framebuffer& framebuffer){
  //---------------------------

  vk_depth->create_depth_image(&framebuffer.depth);
  vk_color->create_color_image(&framebuffer.color);
  vk_color->create_color_image(&framebuffer.color_resolve);

  framebuffer.vec_attachment.push_back(framebuffer.color.view);
  framebuffer.vec_attachment.push_back(framebuffer.depth.view);
  //framebuffer.vec_attachment.push_back(framebuffer.color_resolve.view);

  //---------------------------
}
void Framebuffer::create_framebuffer_handle(vk::structure::Renderpass& renderpass, vk::structure::Framebuffer& framebuffer){
  //---------------------------

  VkFramebufferCreateInfo framebufferInfo{};
  framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  framebufferInfo.renderPass = renderpass.handle;
  framebufferInfo.attachmentCount = static_cast<uint32_t>(framebuffer.vec_attachment.size());
  framebufferInfo.pAttachments = framebuffer.vec_attachment.data();
  framebufferInfo.width = vk_struct->window.extent.width;
  framebufferInfo.height = vk_struct->window.extent.height;
  framebufferInfo.layers = 1;

  VkResult result = vkCreateFramebuffer(vk_struct->device.handle, &framebufferInfo, nullptr, &framebuffer.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create framebuffer!");
  }

  //---------------------------
}
void Framebuffer::clean_framebuffer_image(vk::structure::Framebuffer& framebuffer){
  //---------------------------

  vk_image->clean_image(&framebuffer.color);
  vk_image->clean_image(&framebuffer.color_resolve);
  vk_image->clean_image(&framebuffer.depth);

  //---------------------------
}
void Framebuffer::clean_framebuffer_handle(VkFramebuffer& fbo){
  //---------------------------

  vkDestroyFramebuffer(vk_struct->device.handle, fbo, nullptr);

  //---------------------------
}

}
