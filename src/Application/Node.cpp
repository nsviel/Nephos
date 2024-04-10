#include "Node.h"
#include "Configuration.h"

#include <GUI/Node.h>
#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <iostream>


namespace app{

//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->config = new Configuration();
  this->node_profiler = new prf::Node();
  this->node_utility = new utl::Node(this);
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
  node_engine->config();
  node_engine->init();
  node_gui->init();

  //---------------------------
}
void Node::loop(){
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  prf::graph::Profiler* profiler = prf_manager->get_profiler_main();
  prf::graph::Tasker* tasker_cpu = profiler->get_or_create_tasker("cpu");
  prf::graph::Tasker* tasker_gpu = profiler->get_or_create_tasker("gpu");
  //---------------------------

  auto start_time = std::chrono::steady_clock::now();
  this->running = true;
  while(running){
    tasker_cpu->loop_begin(120);
    tasker_gpu->loop_begin();

    node_engine->loop();
    node_vulkan->loop();
    node_gui->loop();

    tasker_cpu->loop_end();
    tasker_gpu->loop_end();
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
