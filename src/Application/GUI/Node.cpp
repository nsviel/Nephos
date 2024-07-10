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

  this->gui_demo = new gui::interface::Demo(this);
  this->gui_state = new gui::state::Manager(this);
  this->gui_tab = new gui::Tab(this);
  this->gui_style = new gui::style::Style(this);
  this->gui_font = new gui::style::Font(this);
  this->gui_theme = new gui::style::Theme(this);
  this->gui_docking = new gui::interface::Docking();
  this->tasker = node_engine->get_tasker_cpu();

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete gui_tab;

  //---------------------------
}

//Main function
void Node::init(){
  //---------------------------

  gui_font->init();
  gui_style->init();
  gui_theme->init();
  gui_state->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  tasker->task_begin("gui::loop");

  //A virer dans thread presentation ou pas
  //gui_state->loop();


  gui_tab->loop();
  gui_demo->loop();

  tasker->task_end("gui::loop");

  //---------------------------
}

}
