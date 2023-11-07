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

//Main function
void VK_frame::create_frame(){
  //---------------------------

  for(int i=0; i<struct_vulkan->swapchain.vec_swapchain_image.size(); i++){
    Struct_framebuffer* fbo = new Struct_framebuffer();
    fbo->color.image = struct_vulkan->swapchain.vec_swapchain_image[i];
    fbo->color.format = vk_color->find_color_format();
    fbo->color.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
    fbo->depth.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

    vk_image->create_image_view(&fbo->color);
    vk_depth->create_depth_attachment(fbo);
    vk_framebuffer->create_framebuffer_obj(struct_vulkan->vec_renderpass[2], fbo);
    vk_synchronization->init_frame_sync(fbo);

    struct_vulkan->swapchain.vec_frame.push_back(fbo);
  }

  //---------------------------
}
void VK_frame::clean_frame(){
  vector<Struct_framebuffer*>& vec_frame = struct_vulkan->swapchain.vec_frame;
  //---------------------------

  //Vec images
  for(int i=0; i<vec_frame.size(); i++){
    Struct_framebuffer* fbo = vec_frame[i];
    vkDestroyImageView(struct_vulkan->device.device, fbo->color.view, nullptr);
    vk_image->clean_image(&fbo->depth);
    vk_framebuffer->clean_framebuffer_obj(fbo);
    vk_synchronization->clean_frame_sync(fbo);
    delete fbo;
  }
  vec_frame.clear();

  //---------------------------
}
