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
  this->eng_data = new eng::scene::Node(this);
  this->eng_renderpass = new ENG_renderpass(this);
  this->eng_capture = new eng::capture::Node(this);

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
  eng_capture->init();

  //---------------------------
}
void Engine::loop(){
  //---------------------------

  eng_camera->loop_cam_mouse();
  eng_data->loop();
  eng_vulkan->loop();
  eng_capture->loop();

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
  eng_capture->reset();

  //---------------------------
}
