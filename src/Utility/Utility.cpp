#include "Utility.h"

#include <../Config.h>
#include <UTL_window/UTL_window.h>
#include <UTL_capture/UTL_capture.h>


//Constructor / Destructor
Utility::Utility(Config* config){
  //---------------------------

  this->utl_window = new UTL_window(config);
  this->utl_capture = new UTL_capture();

  //---------------------------
}
Utility::~Utility(){}

//Main function
void Utility::init(){
  //---------------------------

  utl_window->create_window();
  utl_capture->init();

  //---------------------------
}
void Utility::loop(){
  //---------------------------

  utl_window->manage_input();
  utl_window->window_should_close();
  utl_window->check_for_resizing();

  //---------------------------
}
void Utility::exit(){
  //---------------------------

  utl_window->destroy_window();

  //---------------------------
}
