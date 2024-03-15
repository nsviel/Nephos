#include "App_main.h"
#include "Configuration.h"

#include <GUI/Node.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <iostream>


//Constructor / Destructor
App_main::App_main(){
  //---------------------------

  this->config = new Configuration();
  this->node_profiler = new prf::Node();
  this->node_utility = new utl::Node(this);
  this->node_engine = new eng::Node(this);
  this->node_gui = new gui::Node(this);

  //---------------------------
}
App_main::~App_main(){}

//Main function
void App_main::run(){
  //---------------------------

  this->init();
  this->loop();
  this->end();

  //---------------------------
}

//Subfunction
void App_main::init(){
  //---------------------------

  node_utility->init();
  node_engine->config();
  node_engine->init();
  node_gui->init();

  //---------------------------
}
void App_main::loop(){
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  prf::graph::Profiler* profiler = prf_manager->get_profiler_main();
  prf::graph::Tasker* tasker_cpu = profiler->get_or_create_tasker("cpu");
  prf::graph::Tasker* tasker_gpu = profiler->get_or_create_tasker("gpu");
  //---------------------------

  auto start_time = std::chrono::steady_clock::now();
  while(config->run_app){
    tasker_cpu->loop_begin(120);
    tasker_gpu->loop_begin();

    node_engine->loop();
    node_utility->loop();
    node_gui->loop();

    tasker_cpu->loop_end();
    tasker_gpu->loop_end();
  }

  //---------------------------
}
void App_main::end(){
  //---------------------------

  node_gui->clean();
  node_engine->clean();
  node_utility->clean();

  //---------------------------
}
