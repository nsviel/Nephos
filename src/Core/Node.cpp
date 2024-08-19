#include "Node.h"

#include <Application/Node.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>
#include <IO/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Module/Namespace.h>
#include <Data/Namespace.h>


namespace core{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------
sayHello();
  this->node_app = node_app;

  this->node_vulkan = node_app->get_node_vulkan();

  this->thread_pool = new sys::thread::task::Pool(50);
  this->node_data = new dat::Node(this);
  this->node_module = new mod::Node(this);

  this->node_dynamic = new dyn::Node(this);

  this->node_engine = new eng::Node(this);
  this->node_io = new io::Node(this);

  //Tasker CPU
  prf::Node* node_profiler = node_engine->get_node_profiler();
  prf::dynamic::Manager* prf_dynamic = node_profiler->get_prf_dynamic();
  this->tasker = prf_dynamic->get_tasker_cpu();
sayHello();
  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_data->init();
  node_io->init();
  node_engine->init();
  node_module->init();
  node_dynamic->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  tasker->task_begin("eng::loop");
  node_data->loop();
  node_engine->loop();
  node_dynamic->loop();
  node_module->loop();
  tasker->task_end("eng::loop");

  tasker->task_begin("eng::vulkan");
  node_vulkan->loop();
  tasker->task_end("eng::vulkan");

  //---------------------------
}
void Node::gui(){
  //---------------------------

  tasker->task_begin("eng::gui");

  node_data->gui();
  node_io->gui();
  node_engine->gui();
  node_dynamic->gui();
  node_module->gui();

  tasker->task_end("eng::gui");

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_data->clean();
  node_io->clean();
  node_vulkan->clean();
  node_dynamic->clean();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_engine->reset();
  node_data->reset();
  node_dynamic->reset();

  //---------------------------
}
void Node::close(){
  //---------------------------

  node_app->close();

  //---------------------------
}

}
