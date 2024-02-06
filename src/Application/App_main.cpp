#include "App_main.h"
#include "Config.h"

#include <GUI/Node.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <iostream>


//Constructor / Destructor
App_main::App_main(){
  //---------------------------

  this->config = new Config();
  this->node_utility = new utl::Node(config);
  this->node_engine = new eng::Node(node_utility);
  this->node_gui = new gui::Node(node_utility, node_engine);
  this->fps_control = new utl::fps::Control(120);

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
  utl::element::Profiler* cpu_profiler = node_utility->get_cpu_profiler();
  //---------------------------

  auto start_time = std::chrono::steady_clock::now();
  while(config->run_app){
    cpu_profiler->loop_begin();

    fps_control->start();
    node_engine->loop();
    node_utility->loop();
    node_gui->loop();

    cpu_profiler->task_begin("sleep");
    fps_control->stop();
    cpu_profiler->task_end("sleep", vec4(50, 50, 50, 255));
    cpu_profiler->loop_end();
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
