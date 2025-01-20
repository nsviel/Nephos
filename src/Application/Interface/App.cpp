#include "App.h"

#include <iostream>
#include <stdexcept>



//Constructor / Destructor
App::App(){
  //---------------------------


  //---------------------------
}
App::~App(){}

//Main function
void App::init(){
  //---------------------------
  
  node_app.init();

  // Start the node_app loop in a separate thread
  this->thread = std::thread([this]() {
    node_app.loop();  // Run the app loop
    node_app.end();   // Clean up after the loop
  });

  //---------------------------
}
void App::run(){
  //---------------------------

  this->thread.join();

  //---------------------------
}
void App::add_cloud(){
  //---------------------------

  std::cout<<"coucou"<<std::endl;


  //---------------------------
}
