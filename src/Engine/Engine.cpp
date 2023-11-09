#include "Engine.h"

#include <ELE_window/ELE_window.h>
#include <Vulkan.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_render.h>
#include <ENG_data/ENG_data.h>
#include <ENG_camera/ENG_camera.h>
#include <ENG_shader/ENG_shader.h>
#include <ENG_render/ENG_renderpass.h>


//Constructor / Destructor
Engine::Engine(ELE_window* ele_window){
  //---------------------------

  this->ele_window = ele_window;
  this->eng_camera = new ENG_camera(this);
  this->eng_shader = new ENG_shader(this);
  this->eng_vulkan = new Vulkan(ele_window);
  this->eng_data = new ENG_data(this);
  this->eng_renderpass = new ENG_renderpass(this);

  //---------------------------
}
Engine::~Engine(){
  //---------------------------

  delete eng_camera;
  delete eng_shader;
  delete eng_data;

  //---------------------------
}

void Engine::init(){
  //---------------------------

  eng_renderpass->init_renderpass();
  eng_vulkan->init();
  eng_data->init();

  //---------------------------
}
void Engine::loop(){
  //---------------------------

  eng_camera->loop_cam_mouse();
  eng_data->loop();
  eng_vulkan->loop();

  //---------------------------
}
void Engine::exit(){
  //---------------------------

  eng_vulkan->clean();

  //---------------------------
}
void Engine::wait_for_gpu_idle(){
  //---------------------------

  eng_vulkan->wait();

  //---------------------------
}
void Engine::reset(){
  //---------------------------

  eng_camera->reset();
  eng_data->reset();

  //---------------------------
}
