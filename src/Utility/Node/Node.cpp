#include "Node.h"

#include <Config.h>


namespace util{

//Constructor / Destructor
Node::Node(Config* config){
  //---------------------------

  this->utl_window = new util::element::Window(config);
  this->utl_capture = new util::capture::Node();

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
