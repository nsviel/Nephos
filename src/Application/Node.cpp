#include "Node.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace app{

//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->node_vulkan = new vk::Node(&running);
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
  node_gui->init();
  node_scene->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  while(running){
    node_scene->loop();
    node_gui->loop();
    node_engine->loop();
  }

  //---------------------------
}
void Node::end(){
  //---------------------------

  node_scene->clean();
  node_engine->clean();

  //---------------------------
}

}
