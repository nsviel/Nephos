#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


namespace eng{

//Constructor / Destructor
Node::Node(utl::Node* node_utility){
  //---------------------------

  this->node_utility = node_utility;
  this->cpu_profiler = node_utility->get_cpu_profiler();
  this->eng_vulkan = new vk::Node(this);
  this->node_camera = new eng::cam::Node(this);
  this->node_scene = new eng::scene::Node(this);
  this->node_operation = new eng::ope::Node(this);
  this->node_render = new eng::render::Node(this);
  this->node_capture = new eng::capture::Node(this);
  this->node_gui = new eng::gui::Node(this);

  this->add_node_panel(node_operation);
  this->add_node_panel(node_camera);
  this->add_node_panel(node_scene);
  this->add_node_panel(node_capture);
  this->add_node_panel(node_render);
  this->add_node_panel(node_gui);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_render->init();
  eng_vulkan->init();
  node_scene->init();
  node_capture->init();
  node_camera->init();

  //---------------------------
}
void Node::loop(){
  cpu_profiler->task_begin("eng");
  //---------------------------

  node_camera->loop();

  cpu_profiler->task_begin("eng::scene");
  node_scene->loop();
  cpu_profiler->task_end("eng::scene");

  cpu_profiler->task_begin("eng::vulkan");
  eng_vulkan->loop();
  cpu_profiler->task_end("eng::vulkan");

  cpu_profiler->task_begin("eng::capture");
  node_capture->loop();
  cpu_profiler->task_end("eng::capture");

  //---------------------------
  cpu_profiler->task_end("eng");

}
void Node::gui(){
  cpu_profiler->task_begin("eng::gui");
  //---------------------------

  node_scene->gui();
  node_render->gui();
  node_capture->gui();
  node_camera->gui();
  node_gui->gui();

  //---------------------------
  cpu_profiler->task_end("eng::gui");
  node_operation->gui();
}
void Node::exit(){
  //---------------------------

  eng_vulkan->clean();

  //---------------------------
}
void Node::wait(){
  //---------------------------

  eng_vulkan->wait();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_camera->reset();
  node_scene->reset();

  //---------------------------
}

}
