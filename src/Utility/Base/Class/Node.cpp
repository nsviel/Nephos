#include "Node.h"


namespace utl::base{

std::vector<utl::gui::Panel*> Node::vec_panel;
utl::base::Node* Node::root;

//Constructor / Destructor
Node::Node(){
  //---------------------------


  //---------------------------
}
Node::~Node(){}

//Subfunction
utl::gui::Panel* Node::add_panel(std::string name, std::string icon, bool value){
  //---------------------------

  utl::gui::Panel* panel = new utl::gui::Panel(name, icon, value);
  Node::vec_panel.push_back(panel);

  //---------------------------
  return panel;
}

}
