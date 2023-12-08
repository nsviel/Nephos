#include "Editor.h"

#include <GUI.h>


namespace gui::dev::panel{

//Constructor / Destructor
Editor::Editor(GUI* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------

  this->editor = new gui::editor::Text(gui);

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
