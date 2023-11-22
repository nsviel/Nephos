#include "DEV_command.h"

#include <GUI.h>
#include <GUI_interface/GUI_tab.h>
#include <TAB_dev/TAB_dev.h>
#include <TAB_dev/DEV_config/DEV_panel.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
DEV_command::DEV_command(GUI* gui){
  //---------------------------

  GUI_tab* gui_tab = gui->get_gui_tab();
  TAB_dev* gui_tab_dev = gui_tab->get_gui_dev();
  this->gui = gui;
  this->gui_dev_panel = gui_tab_dev->get_dev_panel();

  //---------------------------
}
DEV_command::~DEV_command(){}

//Main function
void DEV_command::run_panel(){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
  ImGui::Begin("Command", NULL, ImGuiWindowFlags_AlwaysAutoResize);

  this->design_panel();

  ImGui::End();
  ImGui::PopStyleColor();

  //---------------------------
}
void DEV_command::design_panel(){
  //---------------------------

  if(ImGui::Button(ICON_FA_PLAY)){
    string command = "firefox -P Dev google.fr";
    int err = system(command.c_str());
  }

  if(ImGui::Button("New editor")){
    static bool truc = true;
    gui_dev_panel->vec_editor.push_back(new DEV_code_editor(gui, &truc, "Editor"));
  }

  //---------------------------
}

//Subfunctions
