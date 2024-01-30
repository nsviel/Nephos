#include "Control.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


namespace gui::interface{

//Constructor / Destructor
Control::Control(gui::Node* gui){
  //---------------------------

  utl::Node* utility = gui->get_node_utility();
  eng::Node* engine = gui->get_node_engine();

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
