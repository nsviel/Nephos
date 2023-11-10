#include "VK_engine.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_struct/Struct_synchro.h>
#include <VK_data/VK_data.h>
#include <VK_renderpass/VK_renderpass.h>
#include <VK_command/VK_command_buffer.h>
#include <VK_device/VK_device.h>
#include <VK_presentation/VK_surface.h>
#include <VK_instance/VK_instance.h>
#include <VK_data/VK_canvas.h>
#include <VK_binding/VK_descriptor.h>
#include <VK_image/VK_texture.h>
#include <VK_presentation/VK_swapchain.h>
#include <VK_presentation/VK_frame.h>
#include <VK_shader/VK_reload.h>
#include <VK_drawing/VK_viewport.h>
#include <ELE_window/ELE_window.h>


//Constructor / Destructor
VK_engine::VK_engine(ELE_window* ele_window){
  //---------------------------

  this->ele_window = ele_window;

  this->struct_vulkan = new Struct_vulkan();
  this->struct_synchro = new Struct_synchro();

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

  struct_vulkan->window.glfw_window = ele_window->get_window();
  struct_vulkan->window.window_dim = ele_window->compute_window_dim();

  //Instance
  vk_surface->init_window();
  vk_instance->init_instance();
  vk_surface->init_surface();
  vk_device->init_device();
  vk_command_buffer->create_command_pool();
  vk_descriptor->create_descriptor_pool();
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

  struct_vulkan->window.window_dim = ele_window->compute_window_dim();

  //---------------------------
}
void VK_engine::device_wait_idle(){
  //---------------------------

  vkDeviceWaitIdle(struct_vulkan->device.device);

  //---------------------------
}
void VK_engine::clean(){
  //---------------------------

  vk_texture->clean_textures();
  vk_renderpass->clean_renderpass();
  vk_swapchain->clean_swapchain();
  vk_canvas->clean_canvas();
  vk_data->clean_data_all();
  vk_descriptor->clean_descriptor_pool();
  vk_command_buffer->clean_command_pool();
  vk_device->clean_device();
  vk_surface->clean_surface();
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
  for(int i=0; i<struct_vulkan->list_object.size(); i++){
    Struct_data* data = *next(struct_vulkan->list_object.begin(), i);
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
  for(int i=0; i<struct_vulkan->list_object.size(); i++){
    Struct_data* data = *next(struct_vulkan->list_object.begin(),i);
    if(object->ID == data->object->ID){
      vk_data->clean_data_scene(object->ID);
    }
  }

  //---------------------------
}
