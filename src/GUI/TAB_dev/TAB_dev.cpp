#include "TAB_dev.h"
#include "DEV_config/DEV_panel.h"

#include <GUI.h>
#include <TAB_dev/DEV_editor/DEV_code_editor.h>
#include <TAB_dev/DEV_command/DEV_command.h>


//Constructor / Destructor
TAB_dev::TAB_dev(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->gui_dev_panel = new DEV_panel();

  //---------------------------
}
TAB_dev::~TAB_dev(){}

//Main function
void TAB_dev::create_panels(){
  //---------------------------

  static bool truc = true;
  gui_dev_panel->vec_editor.push_back(new DEV_code_editor(gui, &truc, "Editor"));
  this->gui_dev_command = new DEV_command(gui);

  //---------------------------
}
void TAB_dev::draw_panels(){
  //---------------------------

  gui_dev_panel->run_editors();
  gui_dev_command->run_panel();

  //---------------------------
}
void TAB_dev::open_panels(){
  //---------------------------



  //---------------------------
}
