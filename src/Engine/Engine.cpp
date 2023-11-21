#include "Engine.h"

#include <Utility.h>
#include <Vulkan.h>
#include <ENG_data/ENG_data.h>
#include <ENG_camera/ENG_camera.h>
#include <ENG_shader/ENG_shader.h>
#include <ENG_render/ENG_renderpass.h>


//Constructor / Destructor
Engine::Engine(Utility* utility){
  //---------------------------

  this->utility = utility;
  this->eng_camera = new ENG_camera(this);
  this->eng_shader = new ENG_shader(this);
  this->eng_vulkan = new Vulkan(utility);
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
void Engine::wait(){
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
