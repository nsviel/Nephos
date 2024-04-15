#include "Node.h"

#include <Application/Namespace.h>
#include <GUI/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <iostream>


namespace app{

//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->app_config = new app::Configuration();
  this->node_profiler = new prf::Node();
  this->node_vulkan = new vk::Node(this);
  this->node_engine = new eng::Node(this);
  this->node_gui = new gui::Node(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::run(){
  //---------------------------

  this->init();
  this->loop();
  this->end();

  //---------------------------
}

//Subfunction
void Node::init(){
  //---------------------------

  node_vulkan->init();
  node_engine->init();
  node_gui->init();

  //---------------------------
}
void Node::loop(){
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  //---------------------------

  while(app_config->running){
    prf_manager->loop_begin(120);
    node_engine->loop();
    node_vulkan->loop();
    node_gui->loop();
    prf_manager->loop_end();
  }

  //---------------------------
}
void Node::end(){
  //---------------------------

  node_gui->clean();
  node_engine->clean();
  node_vulkan->clean();

  //---------------------------
}

}
