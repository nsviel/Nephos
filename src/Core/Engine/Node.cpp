#include "Node.h"
#include "Namespace.h"

#include <Core/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Processing/Namespace.h>
#include <Data/Namespace.h>


namespace eng{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  this->node_core = node_core;
  this->node_vulkan = node_core->get_node_vulkan();
  this->node_data = node_core->get_node_data();
  this->node_dynamic = node_core->get_node_dynamic();

  this->node_camera = new cam::Node(this);
  this->node_control = new ctr::Node(this);
  this->node_renderer = new rnd::Node(this);
  this->node_transfor = new eng::trf::Node(this);
  this->node_profiler = new prf::Node(node_core);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_camera->init();
  node_renderer->init();
  node_transfor->init();
  node_profiler->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_camera->loop();
  node_profiler->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_camera->gui();
  node_renderer->gui();
  node_profiler->gui();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_camera->reset();

  //---------------------------
}

}
