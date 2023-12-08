#include "GUI.h"

#include <Engine.h>
#include <Utility.h>
#include <UTL_window/UTL_window.h>
#include <GUI_render/GUI_render.h>
#include <GUI_style/GUI_style.h>
#include <GUI_style/GUI_font.h>
#include <GUI_main/GUI_render/GUI_render.h>


//Constructor / Destructor
GUI::GUI(Utility* utility, Engine* engine){
  //---------------------------

  this->engine = engine;
  this->utility = utility;
  this->utl_window = utility->get_utl_window();

  this->gui_render = new GUI_render(this);
  this->gui_style = new GUI_style(this);
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
