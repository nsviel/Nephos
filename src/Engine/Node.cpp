#include "Node.h"

#include <Application/App_main.h>
#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Camera/Namespace.h>
#include <Scene/Namespace.h>
#include <Capture/Namespace.h>
#include <Render/Namespace.h>


namespace eng{

//Constructor / Destructor
Node::Node(App_main* node_app){
  //---------------------------

  //Dependancy
  this->node_profiler = node_app->get_node_profiler();
  this->node_utility = node_app->get_node_utility();

  //Child
  prf::Manager* profiler = node_profiler->get_profiler_manager();
  this->node_vulkan = new vk::Node(node_utility);
  this->node_scene = new eng::scene::Node(this);
  this->node_camera = new eng::cam::Node(this);
  this->node_operation = new eng::ope::Node(this);
  this->node_render = new eng::render::Node(this);
  this->node_capture = new eng::capture::Node(this);
  this->node_gui = new eng::gui::Node(this);
  this->tasker_cpu = profiler->get_tasker_cpu();

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
  node_vulkan->init();
  node_scene->init();
  node_capture->init();
  node_camera->init();

  //---------------------------
}
void Node::loop(){
  tasker_cpu->task_begin("eng");
  //---------------------------

  tasker_cpu->task_begin("eng::vulkan");
  node_vulkan->loop();
  tasker_cpu->task_end("eng::vulkan");

  node_camera->loop();
  node_capture->loop();

  tasker_cpu->task_begin("eng::scene");
  node_scene->loop();
  tasker_cpu->task_end("eng::scene");

  //---------------------------
  tasker_cpu->task_end("eng");
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

  node_capture->exit();
  node_vulkan->clean();

  //---------------------------
}
void Node::wait(){
  //---------------------------

  node_vulkan->wait();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_camera->reset();
  node_scene->reset();

  //---------------------------
}

}
