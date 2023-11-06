#include "VK_frame.h"

#include <VK_main/VK_engine.h>
#include "../VK_struct/Struct_vulkan.h"
#include "../VK_command/VK_command.h"
#include "../VK_command/VK_synchronization.h"
#include "../VK_presentation/VK_framebuffer.h"
#include "../VK_image/VK_depth.h"
#include "../VK_image/VK_color.h"
#include "../VK_image/VK_image.h"
#include "../VK_device/VK_physical_device.h"


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

//Renderpass frame
void VK_frame::create_frame_renderpass(Struct_renderpass* renderpass){
  //---------------------------

  for(int i=0; i<struct_vulkan->swapchain.vec_swapchain_image.size(); i++){
    Struct_frame* frame = new Struct_frame();

    frame->ID = i;
    frame->color.image_usage = renderpass->color_image_usage;
    frame->color.sampler_layout = renderpass->color_sampler_layout;
    frame->depth.image_usage = renderpass->depth_image_usage;
    frame->depth.sampler_layout = renderpass->depth_sampler_layout;

    vk_color->create_color_attachment(frame);
    vk_depth->create_depth_attachment(frame);
    vk_framebuffer->create_framebuffer(renderpass, frame);

    renderpass->vec_frame.push_back(frame);
  }

  //---------------------------
}
void VK_frame::clean_frame_renderpass(Struct_renderpass* renderpass){
  vector<Struct_frame*>& vec_frame = renderpass->vec_frame;
  //---------------------------

  //Vec images
  for(int i=0; i<vec_frame.size(); i++){
    Struct_frame* frame = vec_frame[i];
    vk_image->clean_image(&frame->color);
    vk_image->clean_image(&frame->depth);
    vk_framebuffer->clean_framebuffer(frame);
    delete frame;
  }
  vec_frame.clear();

  //---------------------------
}

//Swapchain frame
void VK_frame::create_frame_swapchain(){
  //---------------------------

  for(int i=0; i<struct_vulkan->swapchain.vec_swapchain_image.size(); i++){
    Struct_frame* frame = new Struct_frame();

    frame->ID = i;
    frame->color.image = struct_vulkan->swapchain.vec_swapchain_image[i];
    frame->color.format = vk_color->find_color_format();
    frame->color.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
    frame->depth.image_usage = IMAGE_USAGE_DEPTH;

    vk_image->create_image_view(&frame->color);
    vk_depth->create_depth_attachment(frame);
    vk_framebuffer->create_framebuffer(struct_vulkan->vec_renderpass[2], frame);
    vk_synchronization->init_frame_sync(frame);

    struct_vulkan->swapchain.vec_frame.push_back(frame);
  }

  //---------------------------
}
void VK_frame::clean_frame_swapchain(){
  vector<Struct_frame*>& vec_frame = struct_vulkan->swapchain.vec_frame;
  //---------------------------

  //Vec images
  for(int i=0; i<vec_frame.size(); i++){
    Struct_frame* frame = vec_frame[i];
    vkDestroyImageView(struct_vulkan->device.device, frame->color.view, nullptr);
    vk_image->clean_image(&frame->depth);
    vk_framebuffer->clean_framebuffer(frame);
    vk_synchronization->clean_frame_sync(frame);
    delete frame;
  }
  vec_frame.clear();

  //---------------------------
}
