#include "Engine.h"

#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


//Constructor / Destructor
Engine::Engine(utl::Node* node_utility){
  //---------------------------

  utl::element::Window* utl_window = node_utility->get_utl_window();

  this->node_utility = node_utility;
  this->eng_vulkan = new Vulkan(utl_window->get_window());
  this->node_camera = new eng::cam::Node(this);
  this->node_scene = new eng::scene::Node(this);
  this->node_capture = new eng::capture::Node(this);
  this->node_operation = new eng::ope::Node(this);
  this->node_render = new eng::render::Node(this);
  this->eng_renderpass = new eng::renderpass::Manager(node_render);

  //---------------------------
}
Engine::~Engine(){}

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
  node_scene->gui();
  node_render->gui();
  node_operation->gui();

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
