#include "VK_engine.h"

#include <Vulkan/VK_main/Namespace.h>

#include <Utility/Function/Timer/FPS_counter.h>
#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_data/VK_data.h>
#include <Vulkan/VK_device/VK_device.h>
#include <Vulkan/VK_presentation/VK_surface.h>
#include <Vulkan/VK_instance/VK_instance.h>
#include <Vulkan/VK_instance/VK_extension.h>
#include <Vulkan/VK_data/VK_canvas.h>
#include <Vulkan/VK_binding/VK_descriptor.h>
#include <Vulkan/VK_instance/VK_pool.h>
#include <Vulkan/VK_main/VK_texture.h>
#include <Vulkan/VK_presentation/VK_swapchain.h>
#include <Vulkan/VK_presentation/VK_frame.h>
#include <Vulkan/VK_command/VK_synchronization.h>
#include <Vulkan/VK_shader/VK_reload.h>
#include <Vulkan/VK_drawing/VK_viewport.h>
#include <Vulkan/VK_drawing/VK_drawing.h>


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
  this->vk_renderpass = new VK_renderpass(struct_vulkan);
  this->vk_reload = new VK_reload(struct_vulkan);
  this->vk_frame = new VK_frame(struct_vulkan);
  this->vk_canvas = new VK_canvas(struct_vulkan);
  this->vk_drawing = new VK_drawing(struct_vulkan);
  this->vk_synchronization = new VK_synchronization(struct_vulkan);
  this->fps_counter = new FPS_counter();

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
  struct_vulkan->profiler.engine_init = timer.stop_us(t1) / 1000;
}
void VK_engine::init_engine_presentation(){
  //---------------------------

  //Instance
  vk_extension->init();
  vk_instance->init();
  vk_surface->init();
  vk_device->init();
  vk_pool->init();
  vk_canvas->init();

  //Render
  vk_swapchain->create_swapchain();
  vk_viewport->init();
  vk_renderpass->init();
  vk_frame->create_frame();

  //---------------------------
}
void VK_engine::init_engine_headless(){
  //---------------------------

  //Instance
  vk_extension->init();
  vk_instance->init();
  vk_device->init();
  vk_pool->init();
  vk_canvas->init();
  vk_synchronization->init();

  //Render
  vk_viewport->init();
  vk_renderpass->init();

  //---------------------------
}

//Main function
void VK_engine::loop(){
  struct_vulkan->profiler.time_ref = std::chrono::system_clock::now();
  struct_vulkan->profiler.vec_task.clear();
  //---------------------------

  vk_drawing->draw_frame();

  //---------------------------
  struct_vulkan->profiler.engine_fps = fps_counter->update();
}
void VK_engine::clean(){
  //---------------------------

  vk_synchronization->clean();
  vk_texture->clean();
  vk_renderpass->clean();
  vk_swapchain->clean();
  vk_canvas->clean();
  vk_data->clean();
  vk_pool->clean();
  vk_device->clean();
  vk_surface->clean();
  vk_instance->clean();

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
void VK_engine::insert_data_in_engine(utl::base::Data* data){
  if(data == nullptr) return;
  //---------------------------

  //Check if data already in engine
  bool is_in_list = false;
  vk::structure::Object* vk_object;
  for(int i=0; i<struct_vulkan->data.list_vk_object.size(); i++){
    vk_object = *next(struct_vulkan->data.list_vk_object.begin(), i);
    if(data->UID == vk_object->data->UID){
      is_in_list = true;
      break;
    }
  }

  //If not, insert it
  if(is_in_list){
    vk_data->update_data(data, vk_object);
  }else{
    vk_data->insert_data(data);
  }

  //---------------------------
}
void VK_engine::remove_data_in_engine(utl::base::Data* data){
  //---------------------------

  bool is_in_list = false;
  for(int i=0; i<struct_vulkan->data.list_vk_object.size(); i++){
    vk::structure::Object* vk_object = *next(struct_vulkan->data.list_vk_object.begin(),i);
    if(data->UID == vk_object->data->UID){
      vk_data->clean_vk_object(vk_object);
      struct_vulkan->data.list_vk_object.remove(vk_object);
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
