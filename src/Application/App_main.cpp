#include "App_main.h"
#include "../Config.h"

#include <GUI.h>
#include <Engine/Node.h>
#include <iostream>


//Constructor / Destructor
App_main::App_main(){
  //---------------------------

  this->config = new Config();
  this->utility = new utl::Node(config);
  this->engine = new eng::Node(utility);
  this->gui = new GUI(utility, engine);

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

  engine->init();
  gui->init();

  //---------------------------
}
void App_main::loop(){
  //---------------------------

  auto start_time = std::chrono::steady_clock::now();
  while(config->run_app){
    gui->loop();
    engine->loop();
    utility->loop();
  }
  engine->wait();
  gui->wait();

  //---------------------------
}
void App_main::end(){
  //---------------------------

  gui->exit();
  engine->exit();
  utility->exit();

  //---------------------------
}
