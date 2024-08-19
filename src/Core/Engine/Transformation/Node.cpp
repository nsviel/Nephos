#include "Node.h"

#include <Engine/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace eng::trf{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* panel_transfo = add_panel("Transformation", ICON_FA_PEN_TO_SQUARE, false);
  //---------------------------

  this->node_data = node_engine->get_node_data();

  this->trf_io = new eng::trf::IO();
  this->gui_transformation = new eng::trf::gui::Panel(this, &panel_transfo->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  trf_io->init_path();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_transformation->run_panel();

  //---------------------------
}

}
