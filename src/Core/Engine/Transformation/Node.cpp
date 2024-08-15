#include "Node.h"
#include "Namespace.h"

#include <Core/Namespace.h>
#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace eng::trf{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  utl::gui::Panel* panel_transfo = add_panel("Transformation", ICON_FA_PEN_TO_SQUARE, false);
  //---------------------------

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
