#include "Node.h"

#include <Config.h>
#include <Utility/UTL_window/UTL_window.h>
#include <Utility/UTL_capture/UTL_capture.h>


namespace utility{

//Constructor / Destructor
Node::Node(Config* config){
  //---------------------------

  this->utl_window = new UTL_window(config);
  this->utl_capture = new UTL_capture();

  //---------------------------
  this->init();
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  utl_window->create_window();
  utl_capture->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  utl_window->manage_input();
  utl_window->window_should_close();
  utl_window->check_for_resizing();

  //---------------------------
}
void Node::exit(){
  //---------------------------

  utl_window->destroy_window();

  //---------------------------
}

}
