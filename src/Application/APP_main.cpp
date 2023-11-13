#include "APP_main.h"
#include "../config.h"

#include <GUI.h>
#include <Engine.h>
#include <UTL_window/UTL_window.h>
#include <iostream>


//Constructor / Destructor
APP_main::APP_main(){
  //---------------------------

  this->config = new Config();
  this->utl_window = new UTL_window(config);
  this->engine = new Engine(utl_window);
  this->gui = new GUI(utl_window, engine);

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

  utl_window->create_window();
  engine->init();
  gui->init();

  //---------------------------
}
void APP_main::loop(){
  //---------------------------

  auto start_time = std::chrono::steady_clock::now();
  while(!utl_window->window_should_close()){
    gui->loop();
    engine->loop();
    utl_window->manage_input();
  }
  engine->wait();
  gui->wait();

  //---------------------------
}
void APP_main::end(){
  //---------------------------

  gui->exit();
  engine->exit();
  utl_window->destroy_window();

  //---------------------------
}
