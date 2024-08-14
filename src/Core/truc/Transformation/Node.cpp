#include "Node.h"
#include "Namespace.h"

#include <Core/Namespace.h>
#include <Element/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io::trf{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* panel_transfo = add_panel("Transformation", ICON_FA_PEN_TO_SQUARE, false);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_data = node_engine->get_node_data();
  this->node_dynamic = node_engine->get_node_dynamic();

  //Child
  this->io_struct = new io::trf::Structure();
  this->io_transformation = new io::trf::Transformation(this);
  this->gui_transformation = new io::trf::gui::Panel(this, &panel_transfo->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  io_transformation->init_path();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_transformation->run_panel();

  //---------------------------
}

}
