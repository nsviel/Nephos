#include "Node.h"

#include <Application/Node.h>
#include <Engine/Namespace.h>
#include <GUI/Namespace.h>
#include <Utility/Namespace.h>


namespace gui{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  this->node_engine = node_app->get_node_engine();
  this->node_vulkan = node_app->get_node_vulkan();

  this->gui_render = new gui::Render(this);
  this->gui_style = new gui::style::Config(this);
  this->gui_font = new gui::style::Font(this);
  this->gui_theme = new gui::style::Theme(this);
  this->node_tab = new gui::tab::Node(this);
  this->gui_control = new gui::interface::Control(this);
  this->gui_docking = new gui::interface::Docking(this);

  this->add_node_panel(node_tab);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete node_tab;
  delete gui_control;

  //---------------------------
}

//Main function
void Node::init(){
  //---------------------------

  gui_font->init_font();
  gui_style->init_style();
  gui_theme->init_theme();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  gui_render->new_frame();
  gui_docking->docker_space_main();
  node_tab->loop();
  gui_control->run_control();
  gui_render->end_frame();

  //---------------------------
}

}
