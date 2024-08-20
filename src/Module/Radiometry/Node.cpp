#include "Node.h"

#include <Core/Namespace.h>
#include <Profiler/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Processing/Namespace.h>
#include <Utility/Namespace.h>
#include <Engine/Namespace.h>
#include <Data/Namespace.h>


namespace rad{

//Constructor / Destructor
Node::Node(mod::Node* node_module){
  utl::gui::Panel* rad_panel = add_panel("Radiometry", ICON_FA_FILM, true);
  //---------------------------

  //Dependancy
  this->node_core = node_module->get_node_core();
  this->node_vulkan = node_module->get_node_vulkan();
  this->node_data = node_module->get_node_data();
  this->node_profiler = node_module->get_node_profiler();

  //Child
  this->node_correction = new rad::correction::Node(this);
  this->node_calibration = new rad::calibration::Node(this);
  this->gui_panel = new rad::gui::Panel(this, &rad_panel->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  //---------------------------


  //---------------------------
}
void Node::init(){
  //---------------------------

  //node_correction->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

//  node_correction->loop();
  //node_calibration->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

//  gui_panel->run_panel();

  //---------------------------
}
void Node::clean(){
  //---------------------------


  //---------------------------
}


}
