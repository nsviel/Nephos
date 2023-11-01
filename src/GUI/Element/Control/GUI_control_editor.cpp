#include "GUI_control_editor.h"

#include <Ressource/Editor/GUI_editor_text.h>


//Constructor / Destructor
GUI_control_editor::GUI_control_editor(GUI_editor_text* editor){
  //---------------------------

  this->editor = editor;

  //---------------------------
}
GUI_control_editor::~GUI_control_editor(){}

//Main function
void GUI_control_editor::run_control(){
  //---------------------------

  this->control_keyboard_oneAction();

  //---------------------------
}

//Keyboard
void GUI_control_editor::control_keyboard_oneAction(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //CTRL + S - save to file
    if(io.KeysDown[527] && ImGui::IsKeyPressed(ImGuiKey_S)){
      editor->save_to_current_file();
      break;
    }

  }

  //----------------------------
}

//Mouse
