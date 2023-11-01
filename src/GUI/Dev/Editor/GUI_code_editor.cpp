#include "GUI_code_editor.h"

#include <GUI.h>
#include <Ressource/Editor/GUI_editor_text.h>


//Constructor / Destructor
GUI_code_editor::GUI_code_editor(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->editor = new GUI_editor_text(gui);

  //---------------------------
}
GUI_code_editor::~GUI_code_editor(){}

//Main function
void GUI_code_editor::design_panel(){
  //---------------------------

  editor->run_editor();

  //---------------------------
}

//Subfunction
