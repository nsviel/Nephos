#include "Node.h"

#include <Application/Node.h>
#include <Engine/Namespace.h>
#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <Scene/Namespace.h>
#include <Profiler/Namespace.h>


namespace gui{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  this->node_engine = node_app->get_node_engine();
  this->node_scene = node_app->get_node_scene();

  this->gui_tab = new gui::Tab(this);
  this->gui_style = new gui::style::Config(this);
  this->gui_font = new gui::style::Font(this);
  this->gui_theme = new gui::style::Theme(this);
  this->gui_control = new gui::interface::Control(this);
  this->gui_docking = new gui::interface::Docking(this);
  this->gui_state = new gui::interface::State(this);
  this->tasker = node_engine->get_tasker_cpu();

  this->add_node_panel(node_scene);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete gui_tab;
  delete gui_control;

  //---------------------------
}

//Main function
void Node::init(){
  //---------------------------

  gui_font->init_font();
  gui_style->init_style();
  gui_theme->init_theme();
  gui_state->dock_load_state();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  tasker->task_begin("gui::loop");

  ImGui::NewFrame();
  gui_docking->dock_main_node();
  gui_tab->loop();
  gui_control->run_control();

  tasker->task_end("gui::loop");

  //---------------------------
}

}
