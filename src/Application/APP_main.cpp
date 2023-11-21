#include "APP_main.h"
#include "../config.h"

#include <GUI.h>
#include <Engine.h>
#include <Utility.h>
#include <iostream>


//Constructor / Destructor
APP_main::APP_main(){
  //---------------------------

  this->config = new Config();
  this->utility = new Utility(config);
  this->engine = new Engine(utility);
  this->gui = new GUI(utility, engine);

  //---------------------------
}
APP_main::~APP_main(){}

//Main function
void APP_main::run(){
  //---------------------------

  this->init();
  this->loop();
  this->end();

  //---------------------------
}

//Subfunction
void APP_main::init(){
  //---------------------------

  utility->init();
  engine->init();
  gui->init();

  //---------------------------
}
void APP_main::loop(){
  //---------------------------
//!utl_window->window_should_close()
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
void APP_main::end(){
  //---------------------------

  gui->exit();
  engine->exit();
  utility->exit();

  //---------------------------
}
