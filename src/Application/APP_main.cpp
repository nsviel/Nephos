#include "APP_main.h"
#include "../config.h"

#include <GUI.h>
#include <Engine.h>
#include <ELE_window/ELE_window.h>
#include <iostream>


//Constructor / Destructor
APP_main::APP_main(){
  //---------------------------

  this->config = new Config();
  this->ele_window = new ELE_window(config);
  this->engine = new Engine(ele_window);
  this->gui = new GUI(ele_window, engine);

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

  ele_window->create_window();
  engine->init();
  gui->init();

  //---------------------------
}
void APP_main::loop(){
  //---------------------------

  auto start_time = std::chrono::steady_clock::now();
  while(!ele_window->window_should_close()){
    gui->loop();
    engine->loop();
    ele_window->manage_input();
  }
  gui->wait();

  //---------------------------
}
void APP_main::end(){
  //---------------------------

  gui->exit();
  engine->exit();
  ele_window->destroy_window();

  //---------------------------
}
