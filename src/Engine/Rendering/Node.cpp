#include "Node.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Rendering/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace rnd{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* opt_panel = add_panel("Option##456", ICON_FA_COG, false);
  utl::gui::Panel* sha_panel = add_panel("Shader", ICON_FA_ROAD, false);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_operation = node_engine->get_node_operation();

  //Child
  this->gui_option = new rnd::gui::Option(node_engine, &opt_panel->is_open);
  this->gui_shader = new rnd::gui::Shader(node_engine, &sha_panel->is_open);
  this->gui_render = new rnd::gui::Renderer(node_engine);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  gui_shader->init_panel();

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