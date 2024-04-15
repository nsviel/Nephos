#include "Frame.h"

#include <Vulkan/Namespace.h>


namespace vk::presentation{

//Constructor / Destructor
Frame::Frame(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_framebuffer = new vk::renderpass::Framebuffer(vk_struct);
  this->vk_image = new vk::image::Image(vk_struct);
  this->vk_color = new vk::image::Color(vk_struct);
  this->vk_depth = new vk::image::Depth(vk_struct);

  //---------------------------
}
Frame::~Frame(){}

//Main function
void Frame::create_frame(){
  vk::structure::Renderpass* renderpass = vk_struct->render.get_renderpass_byName("gui");
  if(renderpass == nullptr)return;
  //---------------------------

  for(int i=0; i<vk_struct->swapchain.vec_swapchain_image.size(); i++){
    vk::structure::Frame* frame = new vk::structure::Frame();
    frame->color.handle = vk_struct->swapchain.vec_swapchain_image[i];
    frame->color.format = vk_color->find_color_format();
    frame->color.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
    frame->depth.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

    vk_depth->create_depth_image(&frame->depth);
    vk_image->create_image_view(&frame->color);
    vk_framebuffer->create_framebuffer_swapchain(renderpass, frame);

    vk_struct->swapchain.vec_frame.push_back(frame);
  }

  //---------------------------
}
void Frame::clean_frame(){
  vector<vk::structure::Frame*>& vec_frame = vk_struct->swapchain.vec_frame;
  //---------------------------

  //Vec images
  for(int i=0; i<vec_frame.size(); i++){
    vk::structure::Frame* frame = vec_frame[i];
    vkDestroyImageView(vk_struct->device.handle, frame->color.view, nullptr);
    vk_image->clean_image(&frame->depth);
    vk_framebuffer->clean_framebuffer_obj(frame->fbo);
    delete frame;
  }
  vec_frame.clear();

  //---------------------------
}

}
