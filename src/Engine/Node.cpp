#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace eng{

//Constructor / Destructor
Node::Node(utl::Node* node_utility){
  //---------------------------

  this->node_utility = node_utility;
  this->node_profiler = node_utility->get_node_profiler();
  this->eng_vulkan = new vk::Node(node_utility);
  this->node_camera = new eng::cam::Node(this);
  this->node_scene = new eng::scene::Node(this);
  this->node_operation = new eng::ope::Node(this);
  this->node_render = new eng::render::Node(this);
  this->node_capture = new eng::capture::Node(this);
  this->node_gui = new eng::gui::Node(this);
  this->fps_counter = new prf::fps::Counter();
  this->tasker_cpu = node_profiler->get_tasker_cpu();

  this->add_node_panel(node_operation);
  this->add_node_panel(node_camera);
  this->add_node_panel(node_scene);
  this->add_node_panel(node_capture);
  this->add_node_panel(node_render);
  this->add_node_panel(node_profiler);
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
  tasker_cpu->task_begin("eng");
  //---------------------------

  node_camera->loop();

  tasker_cpu->task_begin("eng::scene");
  node_scene->loop();
  tasker_cpu->task_end("eng::scene");

  tasker_cpu->task_begin("eng::vulkan");
  eng_vulkan->loop();
  tasker_cpu->task_end("eng::vulkan");

  //---------------------------
  tasker_cpu->task_end("eng");
  tasker_cpu->set_fps(fps_counter->update());
}
void Node::gui(){
  //---------------------------

  tasker_cpu->task_begin("eng::gui");
  node_scene->gui();
  node_render->gui();
  node_capture->gui();
  node_camera->gui();
  node_gui->gui();
  tasker_cpu->task_end("eng::gui");

  tasker_cpu->task_begin("gui::profiler");
  node_profiler->gui();
  tasker_cpu->task_end("gui::profiler");

  //---------------------------
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
