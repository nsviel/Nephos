#include "App_main.h"
#include "../Config.h"

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

  node_engine->init();
  node_gui->init();

  //---------------------------
}
void App_main::loop(){
  //---------------------------

  auto start_time = std::chrono::steady_clock::now();
  while(config->run_app){
    node_gui->loop();
    node_engine->loop();
    node_utility->loop();
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
