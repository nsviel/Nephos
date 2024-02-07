#include "Node.h"

#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>
#include <Application/Config.h>


namespace utl{

//Constructor / Destructor
Node::Node(Config* config, prf::Node* node_profiler){
  //---------------------------

  this->node_profiler = node_profiler;
  this->utl_window = new utl::element::Window(config);

  utl_window->create_window();

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------



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
