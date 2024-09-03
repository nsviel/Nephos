#include "Node.h"

#include <Application/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <System/Namespace.h>
#include <Engine/Namespace.h>
#include <IO/Namespace.h>
#include <Data/Namespace.h>


namespace core{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  this->thread_pool = new thr::task::Pool(50);

  this->node_vulkan = node_app->get_node_vulkan();
  this->node_system = new sys::Node(this);
  this->node_data = new dat::Node(this);
  this->node_engine = new eng::Node(this);
  this->node_io = new io::Node(this);

  //Tasker CPU
  prf::Node* node_profiler = node_system->get_node_profiler();
  this->tasker = node_profiler->get_tasker_cpu();

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_data->init();
  node_io->init();
  node_engine->init();
  node_system->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_data->loop();
  node_engine->loop();
  node_system->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_data->gui();
  node_io->gui();
  node_engine->gui();

  //Problem here
  node_system->gui();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_data->clean();
  node_io->clean();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_engine->reset();
  node_data->reset();

  //---------------------------
}

}
