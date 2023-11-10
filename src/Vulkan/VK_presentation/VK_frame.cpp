#include "VK_frame.h"

#include <VK_main/VK_engine.h>
#include <VK_struct/Struct_vulkan.h>
#include <VK_command/VK_command.h>
#include <VK_command/VK_synchronization.h>
#include <VK_presentation/VK_framebuffer.h>
#include <VK_image/VK_depth.h>
#include <VK_image/VK_color.h>
#include <VK_image/VK_image.h>
#include <VK_device/VK_physical_device.h>


//Constructor / Destructor
VK_frame::VK_frame(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_physical_device = new VK_physical_device(vk_engine);
  this->vk_image = new VK_image(vk_engine);
  this->vk_synchronization = new VK_synchronization(vk_engine);
  this->vk_color = new VK_color(vk_engine);
  this->vk_framebuffer = new VK_framebuffer(vk_engine);
  this->vk_depth = new VK_depth(vk_engine);

  //---------------------------
}
VK_frame::~VK_frame(){}

//Main function
void VK_frame::create_frame(){
  //---------------------------

  for(int i=0; i<struct_vulkan->swapchain.vec_swapchain_image.size(); i++){
    Struct_renderpass* renderpass = struct_vulkan->get_renderpass_byName("gui");
    if(renderpass == nullptr)return;
    Struct_frame* frame = new Struct_frame();
    frame->image.image = struct_vulkan->swapchain.vec_swapchain_image[i];
    frame->image.format = vk_color->find_color_format();
    frame->image.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
    frame->depth.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

    vk_image->create_image_view(&frame->image);
    vk_depth->create_depth_attachment(&frame->depth);
    vk_framebuffer->create_framebuffer_swapchain(renderpass, frame);
    vk_synchronization->init_frame_sync(frame);

    struct_vulkan->swapchain.vec_frame.push_back(frame);
  }

  //---------------------------
}
void VK_frame::clean_frame(){
  vector<Struct_frame*>& vec_frame = struct_vulkan->swapchain.vec_frame;
  //---------------------------

  //Vec images
  for(int i=0; i<vec_frame.size(); i++){
    Struct_frame* frame = vec_frame[i];
    vkDestroyImageView(struct_vulkan->device.device, frame->image.view, nullptr);
    vk_image->clean_image(&frame->depth);
    vk_framebuffer->clean_framebuffer_obj(frame->fbo);
    vk_synchronization->clean_frame_sync(frame);
    delete frame;
  }
  vec_frame.clear();

  //---------------------------
}
