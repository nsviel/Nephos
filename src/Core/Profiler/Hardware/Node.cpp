#include "Node.h"

#include <Profiler/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace prf::hardware{

Node::Node(prf::Node* node_profiler){
  utl::gui::Panel* prf_panel = add_panel("Profiler", ICON_FA_ARROW_ROTATE_RIGHT, true);
  //---------------------------

  this->node_vulkan = node_profiler->get_node_vulkan();

  this->prf_struct = new prf::hardware::Structure();
  this->prf_manager = new prf::hardware::Manager(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  prf_hardware->init();

  //---------------------------
}

}
