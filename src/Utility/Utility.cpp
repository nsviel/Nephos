#include "Utility.h"

#include <../Config.h>
#include <UTL_window/UTL_window.h>


//Constructor / Destructor
Utility::Utility(Config* config){
  //---------------------------

  this->utl_window = new UTL_window(config);

  //---------------------------
}
Utility::~Utility(){}

//Main function
void Utility::init(){
  //---------------------------

  utl_window->create_window();

  //---------------------------
}
void Utility::loop(){
  //---------------------------

  utl_window->manage_input();

  //---------------------------
}
void Utility::exit(){
  //---------------------------

  utl_window->destroy_window();

  //---------------------------
}
