#include "Node.h"

#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::elm{

//Constructor / Destructor
Node::Node(dat::Node* node_data){
  //---------------------------

  //Dependancy
  this->node_vulkan = node_data->get_node_vulkan();

  //Child
  this->dat_struct = new dat::elm::Structure();
  this->dat_uid = new dat::elm::UID();
  this->dat_set = new dat::elm::Set(this);
  this->dat_entity = new dat::elm::Entity(this);
  this->dat_glyph = new dat::elm::Glyph(this);
  this->dat_image = new dat::elm::Image(this);
  this->gui_set = new dat::set::gui::Panel(this);
  this->gui_entity = new dat::entity::gui::Panel(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::gui(){
  //---------------------------

  gui_entity->run_panel();
  gui_set->run_panel();

  //---------------------------
}

}
