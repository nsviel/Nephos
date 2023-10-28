#include "GUI_dev.h"
#include "GUI_dev_panel.h"

#include <GUI.h>
#include <Dev/Editor/GUI_code_editor.h>
#include <Dev/Command/GUI_dev_command.h>


//Constructor / Destructor
GUI_dev::GUI_dev(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->gui_dev_panel = new GUI_dev_panel();

  //---------------------------
}
GUI_dev::~GUI_dev(){}

//Main function
void GUI_dev::create_panels(){
  //---------------------------

  static bool truc = true;
  gui_dev_panel->vec_editor.push_back(new GUI_code_editor(gui, &truc, "Editor"));
  this->gui_dev_command = new GUI_dev_command(gui);

  //---------------------------
}
void GUI_dev::draw_panels(){
  //---------------------------

  gui_dev_panel->run_editors();
  gui_dev_command->run_panel();

  //---------------------------
}
void GUI_dev::open_panels(){
  //---------------------------



  //---------------------------
}
