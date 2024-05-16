#include "Node.h"

#include <Profiler/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace prf{

Node::Node(){
  utl::gui::Panel* prf_panel = add_panel("Profiler", ICON_FA_ARROW_ROTATE_RIGHT, false);
  //---------------------------

  this->prf_manager = new prf::Manager();
  this->gui_panel = new prf::gui::Panel(this, &prf_panel->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------


  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_panel->run_panel();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  prf_manager->loop_end();
  prf_manager->loop_begin(120);

  //---------------------------
}


}