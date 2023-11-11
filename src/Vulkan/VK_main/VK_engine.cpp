#include "VK_engine.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_data/VK_data.h>
#include <VK_renderpass/VK_renderpass.h>
#include <VK_command/VK_command_buffer.h>
#include <VK_device/VK_device.h>
#include <VK_presentation/VK_surface.h>
#include <VK_instance/VK_instance.h>
#include <VK_instance/VK_extension.h>
#include <VK_data/VK_canvas.h>
#include <VK_binding/VK_descriptor.h>
#include <VK_binding/VK_pool.h>
#include <VK_image/VK_texture.h>
#include <VK_presentation/VK_swapchain.h>
#include <VK_presentation/VK_frame.h>
#include <VK_shader/VK_reload.h>
#include <VK_drawing/VK_viewport.h>


//Constructor / Destructor
VK_engine::VK_engine(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  this->vk_pool = new VK_pool(struct_vulkan);
  this->vk_extension = new VK_extension(struct_vulkan);
  this->vk_instance = new VK_instance(struct_vulkan);
  this->vk_viewport = new VK_viewport(struct_vulkan);
  this->vk_surface = new VK_surface(struct_vulkan);
  this->vk_device = new VK_device(struct_vulkan);
  this->vk_texture = new VK_texture(struct_vulkan);
  this->vk_descriptor = new VK_descriptor(struct_vulkan);
  this->vk_command_buffer = new VK_command_buffer(struct_vulkan);
  this->vk_data = new VK_data(struct_vulkan);
  this->vk_swapchain = new VK_swapchain(struct_vulkan);
  this->vk_renderpass = new VK_renderpass(struct_vulkan);
  this->vk_reload = new VK_reload(struct_vulkan);
  this->vk_frame = new VK_frame(struct_vulkan);
  this->vk_canvas = new VK_canvas(struct_vulkan);

  //---------------------------
}
VK_engine::~VK_engine(){}

//Main function
void VK_engine::init(){
  timer_time t1 = timer.start_t();
  //---------------------------

  //Instance
  vk_extension->init();
  vk_instance->init_instance();
  vk_surface->init();
  vk_device->init();
  vk_pool->init();
  vk_canvas->create_canvas();

  //Rendering
  vk_swapchain->create_swapchain();
  vk_viewport->init_viewport();
  vk_renderpass->init_renderpass();
  vk_frame->create_frame();

  //---------------------------
  struct_vulkan->info.engine_init = timer.stop_us(t1) / 1000;
}
void VK_engine::loop(){
  //---------------------------


  //---------------------------
}
void VK_engine::device_wait_idle(){
  //---------------------------

  VkResult result = vkDeviceWaitIdle(struct_vulkan->device.device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] device wait idle");
  }

  //---------------------------
}
void VK_engine::clean(){
  //---------------------------

  vk_texture->clean_textures();
  vk_renderpass->clean_renderpass();
  vk_swapchain->clean_swapchain();
  vk_canvas->clean_canvas();
  vk_data->clean_data_all();
  vk_pool->clean();
  vk_device->clean();
  vk_surface->clean();
  vk_instance->clean_instance();

  //---------------------------
}
void VK_engine::reload_shader(string shader, string subshader){
  //---------------------------

  vk_reload->hot_shader_reload(shader, subshader);

  //---------------------------
}

//Data function
void VK_engine::insert_object_in_engine(Object* object){
  //---------------------------

  //Check if object already in engine
  bool is_in_list = false;
  for(int i=0; i<struct_vulkan->data.list_object.size(); i++){
    Struct_entity* data = *next(struct_vulkan->data.list_object.begin(), i);
    if(object->ID == data->object->ID){
      is_in_list = true;
    }
  }

  //If not, insert it
  if(is_in_list == false){
    vk_data->insert_object(object);
  }

  //---------------------------
}
void VK_engine::remove_object_in_engine(Object* object){
  //---------------------------

  bool is_in_list = false;
  for(int i=0; i<struct_vulkan->data.list_object.size(); i++){
    Struct_entity* data = *next(struct_vulkan->data.list_object.begin(),i);
    if(object->ID == data->object->ID){
      vk_data->clean_data_scene(object->ID);
    }
  }

  //---------------------------
}
