#include "VK_engine.h"

#include <VK_main/Namespace.h>

#include <Utility/UTL_specific/FPS_counter.h>
#include <VK_struct/Namespace.h>
#include <VK_data/VK_data.h>
#include <VK_device/VK_device.h>
#include <VK_render/VK_surface.h>
#include <VK_instance/VK_instance.h>
#include <VK_instance/VK_extension.h>
#include <VK_data/VK_canvas.h>
#include <VK_binding/VK_descriptor.h>
#include <VK_instance/VK_pool.h>
#include <VK_main/VK_texture.h>
#include <VK_render/VK_swapchain.h>
#include <VK_render/VK_frame.h>
#include <VK_command/VK_synchronization.h>
#include <VK_shader/VK_reload.h>
#include <VK_drawing/VK_viewport.h>
#include <VK_drawing/VK_drawing.h>


//Constructor / Destructor
VK_engine::VK_engine(vk::structure::Vulkan* struct_vulkan){
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
  this->vk_data = new VK_data(struct_vulkan);
  this->vk_swapchain = new VK_swapchain(struct_vulkan);
  this->vk_renderpass = new vk::Renderpass(struct_vulkan);
  this->vk_reload = new VK_reload(struct_vulkan);
  this->vk_frame = new VK_frame(struct_vulkan);
  this->vk_canvas = new VK_canvas(struct_vulkan);
  this->vk_drawing = new VK_drawing(struct_vulkan);
  this->vk_synchronization = new VK_synchronization(struct_vulkan);
  this->fps_counter = new FPS_counter(60);

  //---------------------------
}
VK_engine::~VK_engine(){}

//Init function
void VK_engine::init(){
  timer_time t1 = timer.start_t();
  //---------------------------

  if(struct_vulkan->param.headless){
    this->init_engine_headless();
  }else{
    this->init_engine_presentation();
  }

  //---------------------------
  struct_vulkan->info.engine_init = timer.stop_us(t1) / 1000;
}
void VK_engine::init_engine_presentation(){
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
}
void VK_engine::init_engine_headless(){
  //---------------------------

  //Instance
  vk_extension->init();
  vk_instance->init_instance();
  vk_device->init();
  vk_pool->init();
  vk_canvas->create_canvas();
  vk_synchronization->init();

  //Rendering
  vk_viewport->init_viewport();
  vk_renderpass->init_renderpass();

  //---------------------------
}

//Main function
void VK_engine::loop(){
  //---------------------------

  vk_drawing->draw_frame();

  //---------------------------
  fps_counter->update();
  struct_vulkan->info.engine_fps = fps_counter->get_fps();
}
void VK_engine::clean(){
  //---------------------------

  vk_synchronization->clean();
  vk_texture->clean_textures();
  vk_renderpass->clean_renderpass();
  vk_swapchain->clean_swapchain();
  vk_canvas->clean_canvas();
  vk_data->clean_entity_all();
  vk_pool->clean();
  vk_device->clean();
  vk_surface->clean();
  vk_instance->clean_instance();

  //---------------------------
}

//Specific function
void VK_engine::device_wait_idle(){
  //---------------------------

  VkResult result = vkDeviceWaitIdle(struct_vulkan->device.device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] device wait idle");
  }

  //---------------------------
}
void VK_engine::reload_shader(string shader, string subshader){
  //---------------------------

  vk_reload->hot_shader_reload(shader, subshader);

  //---------------------------
}

//Data function
void VK_engine::insert_object_in_engine(eng::structure::Object* object){
  //---------------------------

  //Check if object already in engine
  bool is_in_list = false;
  for(int i=0; i<struct_vulkan->data.list_object.size(); i++){
    vk::structure::Entity* data = *next(struct_vulkan->data.list_object.begin(), i);
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
void VK_engine::remove_object_in_engine(eng::structure::Object* object){
  //---------------------------

  bool is_in_list = false;
  for(int i=0; i<struct_vulkan->data.list_object.size(); i++){
    vk::structure::Entity* data = *next(struct_vulkan->data.list_object.begin(),i);
    if(object->ID == data->object->ID){
      vk_data->clean_entity(data);
      struct_vulkan->data.list_object.remove(data);
    }
  }

  //---------------------------
}

//Renderpass function
void VK_engine::add_renderpass_description(vk::structure::Renderpass* renderpass){
  //---------------------------

  struct_vulkan->render.vec_renderpass.push_back(renderpass);

  //---------------------------
}
vk::structure::Renderpass* VK_engine::get_renderpass(int i){
  //---------------------------

  return struct_vulkan->render.vec_renderpass[i];

  //---------------------------
}
vk::structure::Renderpass* VK_engine::get_renderpass_presentation(int i){
  //---------------------------

  return struct_vulkan->render.get_renderpass_byName("gui");

  //---------------------------
}
