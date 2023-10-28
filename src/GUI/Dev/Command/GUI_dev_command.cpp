#include "GUI_dev_command.h"

#include <GUI.h>
#include <Tab/GUI_tab.h>
#include <Dev/Panel/GUI_dev.h>
#include <Dev/Panel/GUI_dev_panel.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
GUI_dev_command::GUI_dev_command(GUI* gui){
  //---------------------------

  GUI_tab* gui_tab = gui->get_gui_tab();
  GUI_dev* gui_dev = gui_tab->get_gui_dev();
  this->gui = gui;
  this->gui_dev_panel = gui_dev->get_dev_panel();

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
    static bool truc = true;
    gui_dev_panel->vec_editor.push_back(new GUI_code_editor(gui, &truc, "Editor"));
  }

  //---------------------------
}

//Subfunctions
