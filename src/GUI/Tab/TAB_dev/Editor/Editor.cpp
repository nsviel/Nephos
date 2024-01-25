#include "Editor.h"

#include <GUI/Node.h>


namespace gui::dev::editor{

//Constructor / Destructor
Editor::Editor(gui::Node* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------

  this->editor = new utl::gui::editor::Text();

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
