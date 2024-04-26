#include "Node.h"

#include <Application/Node.h>
#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Camera/Namespace.h>
#include <Scene/Namespace.h>
#include <Capture/Namespace.h>
#include <Module/Node.h>
#include <Rendering/Namespace.h>


namespace eng{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  //Dependancy
  this->node_profiler = node_app->get_node_profiler();
  this->node_vulkan = node_app->get_node_vulkan();

  //Child
  this->node_scene = new eng::scene::Node(this);
  this->node_camera = new eng::cam::Node(this);
  this->node_capture = new eng::capture::Node(this);
  this->node_module = new eng::module::Node(this);
  this->node_rendering = new rnd::Node(this);

  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  prf::graph::Profiler* profiler = prf_manager->get_profiler_main();
  this->tasker_main =  profiler->get_or_create_tasker("cpu");

  this->add_node_panel(node_camera);
  this->add_node_panel(node_scene);
  this->add_node_panel(node_capture);
  this->add_node_panel(node_profiler);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_capture->config();
  node_scene->init();
  node_capture->init();
  node_camera->init();
  node_module->init();
  node_rendering->init();

  //---------------------------
}
void Node::loop(){
  tasker_main->task_begin("eng");
  //---------------------------

  node_camera->loop();
  node_capture->loop();

  tasker_main->task_begin("eng::scene");
  node_scene->loop();
  tasker_main->task_end("eng::scene");

  //---------------------------
  tasker_main->task_end("eng");
}
void Node::gui(){
  //---------------------------

  tasker_main->task_begin("eng::gui");
  node_scene->gui();
  node_capture->gui();
  node_camera->gui();
  node_module->gui();
  node_rendering->gui();
  tasker_main->task_end("eng::gui");

  tasker_main->task_begin("gui::profiler");
  node_profiler->gui();
  tasker_main->task_end("gui::profiler");

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_capture->clean();
  node_scene->clean();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_camera->reset();
  node_scene->reset();

  //---------------------------
}

}
