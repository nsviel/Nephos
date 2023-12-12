#include "Engine.h"

#include <Utility/Element/Namespace.h>
#include <Vulkan/Vulkan.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Render/ENG_renderpass.h>


//Constructor / Destructor
Engine::Engine(util::Node* utility){
  //---------------------------

  util::element::Window* utl_window = utility->get_utl_window();

  this->utility = utility;
  this->eng_camera = new eng::camera::Node(this);
  this->eng_shader = new eng::shader::Shader(this);
  this->eng_vulkan = new Vulkan(utl_window->get_window());
  this->eng_data = new eng::data::Node(this);
  this->eng_renderpass = new ENG_renderpass(this);
  this->utl_capture = new util::capture::Node();

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
  utl_capture->init();

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
