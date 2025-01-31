#include "Framebuffer.h"

#include <Vulkan/Namespace.h>


namespace vk::renderpass{

//Constructor / Destructor
Framebuffer::Framebuffer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_color = new vk::image::Color(vk_struct);
  this->vk_depth = new vk::image::Depth(vk_struct);
  this->vk_image = new vk::image::Ressource(vk_struct);

  //---------------------------
}
Framebuffer::~Framebuffer(){}

//Main function
void Framebuffer::create_framebuffer(vk::structure::Renderpass& renderpass){
  //---------------------------

  this->create_window_framebuffer(renderpass);
  this->create_screenshot_framebuffer(renderpass);

  //---------------------------
}
void Framebuffer::clean_framebuffer(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Window framebuffer
  vk::structure::Framebuffer& fb_window = renderpass.framebuffer.window;
  this->clean_framebuffer_image(fb_window);
  this->clean_framebuffer_handle(fb_window.handle);

  //Screenshot framebuffer
  if(renderpass.with_screenshot){
    vk::structure::Framebuffer& fb_screenshot = renderpass.framebuffer.screenshot;
    this->clean_framebuffer_image(fb_screenshot);
    this->clean_framebuffer_handle(fb_screenshot.handle);
  }

  //---------------------------
}

//Subfunction
void Framebuffer::create_window_framebuffer(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Window framebuffer
  vk::structure::Framebuffer& framebuffer = renderpass.framebuffer.window;
  framebuffer.color.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  framebuffer.color.layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  framebuffer.depth.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  framebuffer.depth.layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

  //Color image
  vk_color->create_window_image(&framebuffer.color);
  framebuffer.vec_attachment.push_back(framebuffer.color.view);
  framebuffer.width = framebuffer.color.width;
  framebuffer.height = framebuffer.color.height;

  //Depth image
  vk_depth->create_window_image(&framebuffer.depth);
  framebuffer.vec_attachment.push_back(framebuffer.depth.view);

  //Create fb handle
  this->create_framebuffer_handle(renderpass, framebuffer);

  //---------------------------
}
void Framebuffer::create_screenshot_framebuffer(vk::structure::Renderpass& renderpass){
  if(!renderpass.with_screenshot) return;
  //---------------------------

  //Window framebuffer
  vk::structure::Framebuffer& framebuffer = renderpass.framebuffer.screenshot;
  framebuffer.color.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  framebuffer.color.layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  framebuffer.depth.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  framebuffer.depth.layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

  //Color image
  vk_color->create_screenshot_image(&framebuffer.color);
  framebuffer.vec_attachment.push_back(framebuffer.color.view);
  framebuffer.width = framebuffer.color.width;
  framebuffer.height = framebuffer.color.height;

  //Depth image
  vk_depth->create_screenshot_image(&framebuffer.depth);
  framebuffer.vec_attachment.push_back(framebuffer.depth.view);

  //Create fb handle
  this->create_framebuffer_handle(renderpass, framebuffer);

  //---------------------------
}
void Framebuffer::create_framebuffer_handle(vk::structure::Renderpass& renderpass, vk::structure::Framebuffer& framebuffer){
  //---------------------------

  VkFramebufferCreateInfo fb_info{};
  fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  fb_info.renderPass = renderpass.handle;
  fb_info.attachmentCount = static_cast<uint32_t>(framebuffer.vec_attachment.size());
  fb_info.pAttachments = framebuffer.vec_attachment.data();
  fb_info.width = framebuffer.width;
  fb_info.height = framebuffer.height;
  fb_info.layers = 1;

  VkResult result = vkCreateFramebuffer(vk_struct->core.device.handle, &fb_info, nullptr, &framebuffer.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create framebuffer!");
  }

  //---------------------------
}
void Framebuffer::clean_framebuffer_image(vk::structure::Framebuffer& framebuffer){
  //---------------------------

  vk_image->clean_image(framebuffer.color);
  vk_image->clean_image(framebuffer.color_resolve);
  vk_image->clean_image(framebuffer.depth);

  framebuffer.vec_attachment.clear();

  //---------------------------
}
void Framebuffer::clean_framebuffer_handle(VkFramebuffer& fbo){
  //---------------------------

  vkDestroyFramebuffer(vk_struct->core.device.handle, fbo, nullptr);

  //---------------------------
}

}
