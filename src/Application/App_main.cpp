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
  node_engine->init();
  node_gui->init();

  //---------------------------
}
void App_main::loop(){
  prf::Manager* profiler = node_profiler->get_prf_profiler();
  prf::Tasker* tasker_cpu = profiler->get_tasker_cpu();
  //---------------------------

  auto start_time = std::chrono::steady_clock::now();
  while(config->run_app){
    tasker_cpu->loop_begin(120);

    node_engine->loop();
    node_utility->loop();
    node_gui->loop();

    tasker_cpu->loop_end();
  }
  node_engine->wait();
  node_gui->wait();

  //---------------------------
}
void App_main::end(){
  //---------------------------

  node_gui->exit();
  node_engine->exit();
  node_utility->exit();

  //---------------------------
}
