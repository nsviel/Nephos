#include "Node.h"

#include <Utility/Namespace.h>
#include <Application/Config.h>


namespace utl{

//Constructor / Destructor
Node::Node(Config* config){
  //---------------------------

  this->utl_window = new utl::element::Window(config);

  //---------------------------
  this->init();
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  utl_window->create_window();

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
void Node::gui(){
  //---------------------------


  //---------------------------
}

}
