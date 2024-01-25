#include "VK_frame.h"

#include <Vulkan/Namespace.h>


//Constructor / Destructor
VK_frame::VK_frame(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_synchronization = new vk::command::VK_synchronization(struct_vulkan);
  this->vk_framebuffer = new VK_framebuffer(struct_vulkan);
  this->vk_image = new VK_image(struct_vulkan);
  this->vk_color = new VK_color(struct_vulkan);
  this->vk_depth = new VK_depth(struct_vulkan);

  //---------------------------
}
VK_frame::~VK_frame(){}

//Main function
void VK_frame::create_frame(){
  //---------------------------

  for(int i=0; i<struct_vulkan->swapchain.vec_swapchain_image.size(); i++){
    vk::structure::Renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("gui");
    if(renderpass == nullptr)return;
    vk::structure::Frame* frame = new vk::structure::Frame();
    frame->color.image = struct_vulkan->swapchain.vec_swapchain_image[i];
    frame->color.format = vk_color->find_color_format();
    frame->color.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
    frame->depth.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

    vk_depth->create_depth_image(&frame->depth);
    vk_image->create_image_view(&frame->color);
    vk_framebuffer->create_framebuffer_swapchain(renderpass, frame);
    vk_synchronization->init_frame_sync(frame);

    struct_vulkan->swapchain.vec_frame.push_back(frame);
  }

  //---------------------------
}
void VK_frame::clean_frame(){
  vector<vk::structure::Frame*>& vec_frame = struct_vulkan->swapchain.vec_frame;
  //---------------------------

  //Vec images
  for(int i=0; i<vec_frame.size(); i++){
    vk::structure::Frame* frame = vec_frame[i];
    vkDestroyImageView(struct_vulkan->device.device, frame->color.view, nullptr);
    vk_image->clean_image(&frame->depth);
    vk_framebuffer->clean_framebuffer_obj(frame->fbo);
    vk_synchronization->clean_frame_sync(frame);
    delete frame;
  }
  vec_frame.clear();

  //---------------------------
}
