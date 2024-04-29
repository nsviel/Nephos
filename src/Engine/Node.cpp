#include "Node.h"

#include <Application/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Camera/Namespace.h>
#include <Scene/Namespace.h>
#include <Render/Namespace.h>
#include <Data/Namespace.h>


namespace eng{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  //Dependancy
  this->node_profiler = node_app->get_node_profiler();
  this->node_vulkan = node_app->get_node_vulkan();

  //Child
  this->node_data = new dat::Node(this);
  this->node_scene = new sce::Node(this);
  this->node_camera = new cam::Node(this);
  this->node_render = new rnd::Node(this);


  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  prf::graph::Profiler* profiler = prf_manager->get_profiler_main();
  this->tasker_main =  profiler->get_or_create_tasker("cpu");

  this->add_node_panel(node_camera);
  this->add_node_panel(node_scene);

  this->add_node_panel(node_profiler);
  this->add_node_panel(node_render);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_scene->init();
  node_camera->init();
  node_render->init();

  //---------------------------
}
void Node::loop(){
  tasker_main->task_begin("eng");
  //---------------------------

  node_camera->loop();


  tasker_main->task_begin("scene");
  node_scene->loop();
  tasker_main->task_end("scene");

  //---------------------------
  tasker_main->task_end("eng");
}
void Node::gui(){
  //---------------------------

  tasker_main->task_begin("eng::gui");
  node_scene->gui();
  node_camera->gui();

  node_render->gui();
  tasker_main->task_end("eng::gui");

  tasker_main->task_begin("gui::profiler");
  node_profiler->gui();
  tasker_main->task_end("gui::profiler");

  //---------------------------
}
void Node::clean(){
  //---------------------------

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
