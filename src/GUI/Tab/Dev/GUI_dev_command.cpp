#include "GUI_dev_command.h"

#include <GUI.h>


//Constructor / Destructor
GUI_dev_command::GUI_dev_command(GUI* gui){
  //---------------------------

  this->gui = gui;

  //---------------------------
}
GUI_dev_command::~GUI_dev_command(){}

//Main function
void GUI_dev_command::run_panel(){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
  ImGui::Begin("Command", NULL, ImGuiWindowFlags_AlwaysAutoResize);

  this->design_panel();

  ImGui::End();
  ImGui::PopStyleColor();

  //---------------------------
}
void GUI_dev_command::design_panel(){
  //---------------------------



  //---------------------------
}

//Subfunctions
