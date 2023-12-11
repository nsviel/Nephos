#include "GUI.h"

#include <Engine/Node/Engine.h>
#include <Utility/Element/Window.h>
#include <GUI/GUI_main/Style/GUI_font.h>
#include <GUI/GUI_main/Render/Render.h>


//Constructor / Destructor
GUI::GUI(utility::Node* utility, Engine* engine){
  //---------------------------

  this->engine = engine;
  this->utility = utility;
  this->utl_window = utility->get_utl_window();

  this->gui_render = new gui::Render(this);
  this->gui_style = new gui::Style(this);
  this->gui_font = new GUI_font(this);
  this->gui_tab = new gui::Tab(this);
  this->gui_control = new gui::Control(this);
  this->gui_docking = new gui::Docking(this);

  //---------------------------
}
GUI::~GUI(){
  //---------------------------

  delete gui_tab;
  delete gui_control;

  //---------------------------
}

//Main function
void GUI::init(){
  //---------------------------

  gui_render->init();
  gui_tab->create_panels();
  gui_font->init_gui_font();
  gui_style->gui_style();

  //---------------------------
}
void GUI::loop(){
  //---------------------------

  gui_render->new_frame();
  gui_docking->docker_space_main();
  gui_tab->run_tab();
  gui_control->run_control();
  gui_render->loop();

  //---------------------------
}
void GUI::exit(){
  //---------------------------

  gui_render->clean();

  //---------------------------
}
void GUI::wait(){
  //---------------------------

  //gui_render->wait();

  //---------------------------
}
