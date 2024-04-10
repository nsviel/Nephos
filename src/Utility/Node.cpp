#include "Node.h"

#include <Application/Node.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>
#include <Application/Configuration.h>


namespace utl{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  Configuration* config = node_app->get_configuration();

  this->node_profiler = node_app->get_node_profiler();
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
void Node::clean(){
  //---------------------------

  utl_window->destroy_window();

  //---------------------------
}
void Node::gui(){
  //---------------------------


  //---------------------------
}

}
