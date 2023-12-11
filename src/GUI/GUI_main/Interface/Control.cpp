#include "Control.h"

#include <Node/GUI.h>
#include <Engine/Node/Engine.h>
#include <Utility/Node/Utility.h>
#include <Utility/UTL_window/UTL_window.h>


namespace gui{

//Constructor / Destructor
Control::Control(GUI* gui){
  //---------------------------

  Utility* utility = gui->get_utility();
  Engine* engine = gui->get_engine();

  this->utl_window = utility->get_utl_window();
  this->gui_tab = gui->get_gui_tab();

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::run_control(){
  //---------------------------

  this->control_keyboard_oneAction();

  //---------------------------
}

//Keyboard
void Control::control_keyboard_oneAction(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //Esc key - Close program
    if(ImGui::IsKeyPressed(ImGuiKey_Escape)){
      utl_window->close_window();
    }

    //1 key - Next main tab
    if(ImGui::IsKeyPressed(ImGuiKey_LeftAlt)){
      gui_tab->next_tab();
    }
  }

  //----------------------------
}

//Mouse

}
