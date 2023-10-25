#include "GUI_dev_command.h"

#include <GUI.h>
#include <image/IconsFontAwesome5.h>


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

  if(ImGui::Button(ICON_FA_PLAY)){
    string command = "firefox -P Dev google.fr";
    int err = system(command.c_str());
  }

  if(ImGui::Button("New editor")){
    string command = "firefox -P Dev google.fr";
    int err = system(command.c_str());
  }

  //---------------------------
}

//Subfunctions
