#include "GUI_control_gui.h"

#include <GUI.h>
#include <Engine.h>
#include <ELE_window/Window.h>
#include <GUI_tab/GUI_tab.h>


//Constructor / Destructor
GUI_control_gui::GUI_control_gui(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  this->window = engine->get_window();
  this->gui_tab = gui->get_gui_tab();

  //---------------------------
}
GUI_control_gui::~GUI_control_gui(){}

//Main function
void GUI_control_gui::run_control(){
  //---------------------------

  this->control_keyboard_oneAction();

  //---------------------------
}

//Keyboard
void GUI_control_gui::control_keyboard_oneAction(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //Esc key - Close program
    if(ImGui::IsKeyPressed(ImGuiKey_Escape)){
      window->close_window();
    }

    //1 key - Next main tab
    if(ImGui::IsKeyPressed(ImGuiKey_LeftAlt)){
      gui_tab->next_tab();
    }
  }

  //----------------------------
}

//Mouse
