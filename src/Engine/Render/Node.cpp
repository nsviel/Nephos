#include "Node.h"

#include <Engine/Namespace.h>
#include <Render/Namespace.h>
#include <Camera/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::render{

Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_utility = node_engine->get_node_utility();
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_operation = node_engine->get_node_operation();
  this->node_camera = node_engine->get_node_camera();

  //Child
  this->shader_edl = new rnd::edl::Shader(this);
  this->shader_scene = new rnd::scene::Shader(this);
  this->eng_renderpass = new eng::renderpass::Manager(this);
  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete shader_edl;
  delete shader_scene;

  //---------------------------
}

//Main function
void Node::init(){
  //---------------------------

  eng_renderpass->init();

  //---------------------------
}
void Node::gui(){
  //---------------------------



  //---------------------------
}


}
