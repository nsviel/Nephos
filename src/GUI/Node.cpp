#include "Node.h"

#include <Engine/Namespace.h>
#include <GUI/Namespace.h>
#include <Utility/Namespace.h>


namespace gui{

//Constructor / Destructor
Node::Node(utl::Node* utility, eng::Node* engine){
  //---------------------------

  this->engine = engine;
  this->utility = utility;
  this->utl_window = utility->get_utl_window();

  this->gui_render = new gui::Render(this);
  this->gui_style = new gui::Style(this);
  this->gui_font = new gui::style::Font(this);
  this->gui_tab = new gui::interface::Tab(this);
  this->gui_control = new gui::interface::Control(this);
  this->gui_docking = new gui::interface::Docking(this);
  this->gui_theme = new gui::style::Theme(this);

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

  gui_render->init();
  gui_tab->init_tab();
  gui_font->init_font();
  gui_style->init_style();
  gui_theme->init_theme();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  gui_render->new_frame();
  gui_docking->docker_space_main();

  engine->gui();
  gui_tab->run_tab();
  gui_control->run_control();

  gui_render->loop();

  //---------------------------
}
void Node::exit(){
  //---------------------------

  gui_render->clean();

  //---------------------------
}
void Node::wait(){
  //---------------------------

  //gui_render->wait();

  //---------------------------
}

}
