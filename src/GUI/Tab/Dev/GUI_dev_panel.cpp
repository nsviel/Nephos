#include "GUI_dev_panel.h"
#include "Struct_dev_panel.h"

#include <GUI.h>
#include <Dev/GUI_code_editor.h>


//Constructor / Destructor
GUI_dev_panel::GUI_dev_panel(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->struct_dev_panel = new Struct_dev_panel();

  //---------------------------
}
GUI_dev_panel::~GUI_dev_panel(){}

//Main function
void GUI_dev_panel::create_panels(){
  //---------------------------

  static bool truc = true;
  this->gui_code_editor = new GUI_code_editor(gui, &truc, "Editor");

  //---------------------------
}
void GUI_dev_panel::draw_panels(){
  //---------------------------

  gui_code_editor->run_panel();

  //---------------------------
}
void GUI_dev_panel::open_panels(){
  //---------------------------



  //---------------------------
}
