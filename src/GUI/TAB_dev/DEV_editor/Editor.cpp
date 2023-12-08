#include "Editor.h"

#include <GUI.h>
#include <GUI_editor/EDI_text.h>


namespace gui::dev::panel{

//Constructor / Destructor
Editor::Editor(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->editor = new EDI_text(gui);

  //---------------------------
}
Editor::~Editor(){}

//Main function
void Editor::design_panel(){
  //---------------------------

  editor->run_editor();

  //---------------------------
}

//Subfunction

}
