#include "GUI_control.h"

#include <GUI.h>
#include <Engine.h>
#include <Utility.h>
#include <UTL_window/UTL_window.h>
#include <GUI_tab/GUI_tab.h>


//Constructor / Destructor
GUI_control::GUI_control(GUI* gui){
  //---------------------------

  Utility* utility = gui->get_utility();
  Engine* engine = gui->get_engine();

  this->utl_window = utility->get_utl_window();
  this->gui_tab = gui->get_gui_tab();

  //---------------------------
}
GUI_control::~GUI_control(){}

//Main function
void GUI_control::run_control(){
  //---------------------------

  this->control_keyboard_oneAction();

  //---------------------------
}

//Keyboard
void GUI_control::control_keyboard_oneAction(){
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
