#include "Node.h"

#include <Profiler/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace prf{

Node::Node(){
  utl::gui::Panel* prf_panel = new_panel("Profiler", ICON_FA_ARROW_ROTATE_RIGHT, true);
  //---------------------------

  this->profiler_manager = new prf::Manager();
  this->vulkan_manager = new prf::vulkan::Manager();
  this->gui_panel = new prf::gui::Panel(this, &prf_panel->is_open);
  this->name = "Profiler";

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
