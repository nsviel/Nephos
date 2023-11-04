#include "VK_engine.h"
#include "VK_struct/struct_vulkan.h"
#include "VK_struct/struct_param.h"
#include "VK_data/VK_data.h"
#include "VK_renderpass/VK_renderpass.h"
#include "VK_command/VK_command_buffer.h"
#include "VK_drawing/VK_drawing.h"
#include "VK_device/VK_device.h"
#include "VK_device/VK_physical_device.h"
#include "VK_presentation/VK_surface.h"
#include "VK_instance/VK_instance.h"
#include "VK_instance/VK_validation.h"
#include "VK_presentation/VK_canvas.h"
#include "VK_binding/VK_descriptor.h"
#include "VK_image/VK_texture.h"
#include "VK_presentation/VK_swapchain.h"
#include "VK_presentation/VK_frame.h"
#include <VK_main/VK_viewport.h>
#include "VK_shader/VK_reload.h"
#include "VK_main/VK_imgui.h"

#include <Engine.h>
#include <Param.h>
#include <ELE_window/Window.h>
#include <ELE_specific/FPS_counter.h>


//Constructor / Destructor
VK_engine::VK_engine(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->window = engine->get_window();
  this->fps_counter = new FPS_counter(100);
  this->struct_param = new Struct_param();
  this->struct_vulkan = new Struct_vulkan();

  this->vk_imgui = new VK_imgui(this);
  this->vk_instance = new VK_instance(this);
  this->vk_viewport = new VK_viewport(this);
  this->vk_surface = new VK_surface(this);
  this->vk_physical_device = new VK_physical_device(this);
  this->vk_device = new VK_device(this);
  this->vk_texture = new VK_texture(this);
  this->vk_descriptor = new VK_descriptor(this);
  this->vk_command_buffer = new VK_command_buffer(this);
  this->vk_data = new VK_data(this);
  this->vk_swapchain = new VK_swapchain(this);
  this->vk_renderpass = new VK_renderpass(this);
  this->vk_reload = new VK_reload(this);
  this->vk_frame = new VK_frame(this);
  this->vk_canvas = new VK_canvas(this);
  this->vk_drawing = new VK_drawing(this);

  //---------------------------
}
VK_engine::~VK_engine(){}

//Main function
void VK_engine::init(){
  timer_time t1 = timer.start_t();
  //---------------------------

  //Instance
  vk_surface->init_window();
  vk_instance->init_instance();
  vk_surface->create_window_surface();
  vk_physical_device->init_physical_device();
  vk_device->create_logical_device();
  vk_command_buffer->create_command_pool();
  vk_descriptor->create_descriptor_pool();
  vk_canvas->create_canvas();

  //Pipeline
  vk_swapchain->create_swapchain();
  vk_renderpass->init_renderpass();
  vk_frame->create_frame_swapchain(&struct_vulkan->swapchain);

  //Specific
  vk_viewport->init_viewport();

  //---------------------------
  struct_vulkan->time.engine_init = timer.stop_us(t1) / 1000;
}
void VK_engine::loop_draw_frame(){
  //---------------------------

  vk_drawing->draw_frame();

  //---------------------------
  fps_counter->update();
  struct_vulkan->time.engine_fps = fps_counter->get_fps();
}
void VK_engine::device_wait_idle() {
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
  vk_device->clean_logical_device();
  vk_surface->clean_surface();
  vk_instance->clean_instance();

  //---------------------------
}
void VK_engine::reload_shader(string shader, string subshader){
  //---------------------------

  vk_reload->hot_shader_reload(shader, subshader);

  //---------------------------
}
