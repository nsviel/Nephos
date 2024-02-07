#include "Node.h"

#include <Engine/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace profiler{

Node::Node(eng::Node* engine){
  utl::gui::Panel* prf_panel = new_panel("Profiler", ICON_FA_ARROW_ROTATE_RIGHT, true);
  //---------------------------

  this->engine = engine;
  this->gui_panel = new profiler::gui::Panel(this, &prf_panel->is_open);

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


}
