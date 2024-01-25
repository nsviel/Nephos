#include "Engine.h"

#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


//Constructor / Destructor
Engine::Engine(utl::Node* utility){
  //---------------------------

  utl::element::Window* utl_window = utility->get_utl_window();

  this->utility = utility;
  this->eng_vulkan = new Vulkan(utl_window->get_window());
  this->node_camera = new eng::cam::Node(this);
  this->node_scene = new eng::scene::Node(this);
  this->node_shader = new eng::shader::Node(this);
  this->node_capture = new eng::capture::Node(this);
  this->eng_renderpass = new ENG_renderpass(this);

  //---------------------------
}
Engine::~Engine(){
  //---------------------------

  delete node_camera;
  delete node_shader;
  delete node_scene;

  //---------------------------
}

void Engine::init(){
  //---------------------------

  eng_renderpass->init();
  eng_vulkan->init();
  node_scene->init();
  node_capture->init();
  node_camera->init();

  //---------------------------
}
void Engine::loop(){
  //---------------------------

  node_camera->loop();
  node_scene->loop();
  eng_vulkan->loop();
  node_capture->loop();

  //---------------------------
}
void Engine::gui(){
  //---------------------------

  node_capture->gui();
  node_camera->gui();
  node_scene->gui();

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

  node_camera->reset();
  node_scene->reset();

  //---------------------------
}
