#include "Node.h"

#include <Application/Node.h>
#include <GUI/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <Scene/Namespace.h>
#include <iostream>


namespace app{

//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->node_profiler = new prf::Node();
  this->node_vulkan = new vk::Node(this);
  this->node_engine = new eng::Node(this);
  this->node_scene = new sce::Node(this);
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
  node_scene->init();

  //---------------------------
}
void Node::loop(){
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  //---------------------------

  while(running){
    prf_manager->loop_begin(120);
    node_engine->loop();
    node_scene->loop();
    node_gui->loop();
    node_vulkan->loop();
    prf_manager->loop_end();
  }

  //---------------------------
}
void Node::end(){
  //---------------------------

  node_engine->clean();
  node_vulkan->clean();

  //---------------------------
}

}
