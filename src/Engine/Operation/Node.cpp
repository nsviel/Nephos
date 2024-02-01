#include "Node.h"

#include <Engine/Operation/Namespace.h>


namespace eng::ope{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* prf_panel = new_panel("Profiler", ICON_FA_ARROW_ROTATE_RIGHT, true);
  //---------------------------

  this->ope_control = new eng::ope::gui::Control(node_engine);
  this->gui_profiler = new eng::render::gui::Profiler(node_engine, &prf_panel->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------



  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_profiler->run_panel();

  //---------------------------
}
void Node::control(){
  //---------------------------

  ope_control->run_control();

  //---------------------------
}
void Node::reset(){
  //---------------------------



  //---------------------------
}


}
