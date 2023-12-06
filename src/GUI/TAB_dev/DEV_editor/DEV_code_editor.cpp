#include "DEV_code_editor.h"

#include <GUI.h>
#include <GUI_editor/EDI_text.h>


namespace dev{

//Constructor / Destructor
DEV_code_editor::DEV_code_editor(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->editor = new EDI_text(gui);

  //---------------------------
}
DEV_code_editor::~DEV_code_editor(){}

//Main function
void DEV_code_editor::design_panel(){
  //---------------------------

  editor->run_editor();

  //---------------------------
}

//Subfunction

}
