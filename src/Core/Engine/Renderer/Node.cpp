#include "Node.h"

#include <Core/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Renderer/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace rnd{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  utl::gui::Panel* opt_panel = add_panel("Option##456", ICON_FA_GEAR, false);
  utl::gui::Panel* sha_panel = add_panel("Shader", ICON_FA_ROAD, false);
  //---------------------------

  //Dependancy
  this->node_core = node_core;
  this->node_vulkan = node_core->get_node_vulkan();
  this->node_camera = node_core->get_node_camera();
  this->node_data = node_core->get_node_data();
  this->node_dynamic = node_core->get_node_dynamic();
  this->node_control = node_core->get_node_control();

  //Child
  this->itf_shader = new rnd::Shader(this);
  this->gui_option = new rnd::gui::Option(this, &opt_panel->is_open);
  this->gui_shader = new rnd::gui::Shader(this, &sha_panel->is_open);
  this->gui_render = new rnd::gui::Renderer(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  //gui_shader->init_panel();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_option->run_panel();
  gui_shader->run_panel();
  gui_render->run_panel();

  //---------------------------
}

//Subfunction

}
