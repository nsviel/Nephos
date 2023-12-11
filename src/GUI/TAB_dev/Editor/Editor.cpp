#include "Editor.h"

#include <Node/GUI.h>


namespace gui::dev::editor{

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
