#include "Node.h"

#include <Application/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <IO/Namespace.h>
#include <Data/Namespace.h>


namespace core{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  this->thread_pool = new sys::thread::task::Pool(50);

  this->node_vulkan = node_app->get_node_vulkan();
  this->node_data = new dat::Node(this);
  this->node_profiler = new prf::Node(this);
  this->node_engine = new eng::Node(this);
  this->node_io = new io::Node(this);

  //Tasker CPU
  prf::monitor::Manager* prf_dynamic = node_profiler->get_prf_dynamic();
  this->tasker = prf_dynamic->get_tasker_cpu();

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_data->init();
  node_io->init();
  node_engine->init();
  node_profiler->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  tasker->task_begin("eng::loop");
  node_data->loop();
  node_engine->loop();
  tasker->task_end("eng::loop");

  tasker->task_begin("eng::vulkan");
  //node_vulkan->loop();
  tasker->task_end("eng::vulkan");

  node_profiler->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  tasker->task_begin("eng::gui");
  node_data->gui();
  node_io->gui();
  node_engine->gui();
  tasker->task_end("eng::gui");

  node_profiler->gui();

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
