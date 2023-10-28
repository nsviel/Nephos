#include "Loop.h"
#include "../config.h"

#include <GUI.h>
#include <Engine.h>
#include <GPU/GPU_render.h>
#include <Vulkan/VK_engine.h>
#include <Camera/Camera.h>
#include <Window/Window.h>
#include <iostream>


//Constructor / Destructor
Loop::Loop(){
  //---------------------------

  this->config = new Config();
  this->window = new Window(config);
  this->engine = new Engine(window);
  this->gui = new GUI(window, engine);

  //---------------------------
}
Loop::~Loop(){}

//Main function
void Loop::run(){
  //---------------------------

  this->init();
  this->loop();
  this->end();

  //---------------------------
}

//Subfunction
void Loop::init(){
  //---------------------------

  window->create_window();
  engine->init();
  gui->init();

  //---------------------------
}
void Loop::loop(){
  //---------------------------

  auto start_time = std::chrono::steady_clock::now();
  while(!window->window_should_close()){
    gui->loop();
    engine->loop();
    window->manage_input();
  }
  engine->wait_for_gpu_idle();

  //---------------------------
}
void Loop::end(){
  //---------------------------

  gui->exit();
  engine->exit();
  window->destroy_window();

  //---------------------------
}
