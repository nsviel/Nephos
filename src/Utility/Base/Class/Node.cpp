#include "Node.h"


namespace utl::base{

std::vector<utl::gui::Panel*> Node::vec_panel_shared;

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
  this->vec_panel.push_back(panel);
  Node::vec_panel_shared.push_back(panel);

  //---------------------------
  return panel;
}
void Node::add_node_panel(utl::base::Node* node){
  //---------------------------

  std::vector<utl::gui::Panel*> node_vec_panel = node->get_vec_panel();
  this->vec_panel.insert(vec_panel.end(), node_vec_panel.begin(), node_vec_panel.end());

  //---------------------------
}

}
