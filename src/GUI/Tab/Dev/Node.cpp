#include "Node.h"

#include <GUI/Namespace.h>


namespace dev::gui{

//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->menu = new dev::gui::Menu(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::draw_tab(){
  //---------------------------

  menu->run_tab_menu();
  this->run_editors();

  //---------------------------
}

//Subfunction
void Node::run_editors(){
  //---------------------------



  //---------------------------
}

}
