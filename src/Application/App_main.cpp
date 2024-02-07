#include "App_main.h"
#include "Config.h"

#include <GUI/Node.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <iostream>


//Constructor / Destructor
App_main::App_main(){
  //---------------------------

  this->config = new Config();
  this->node_profiler = new prf::Node();
  this->node_utility = new utl::Node(config, node_profiler);
  this->node_engine = new eng::Node(node_utility);
  this->node_gui = new gui::Node(node_utility, node_engine);
  this->fps_control = new prf::fps::Control(120);

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
  prf::Tasker* tasker_cpu = node_profiler->get_tasker_cpu();
  //---------------------------

  auto start_time = std::chrono::steady_clock::now();
  while(config->run_app){
    tasker_cpu->loop_begin(); // Inclure fps control dans profiler (?)
    fps_control->start();

    node_engine->loop();
    node_utility->loop();
    node_gui->loop();

    tasker_cpu->task_begin("sleep");  //Quoiqu'il en soit il faut clear cette partie ! et refaire profiler gui panel marcher
    fps_control->stop();
    tasker_cpu->task_end("sleep", vec4(50, 50, 50, 255));
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
