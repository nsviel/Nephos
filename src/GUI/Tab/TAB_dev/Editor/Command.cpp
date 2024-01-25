#include "Command.h"

#include <GUI/Node.h>
#include <image/IconsFontAwesome6.h>
#include <GUI/Namespace.h>


namespace gui::dev::editor{

//Constructor / Destructor
Command::Command(gui::Node* gui){
  //---------------------------

  Tab* gui_tab = gui->get_gui_tab();
  //gui::dev::tab::Tab* dev_tab = gui_tab->get_dev_tab();
  this->gui = gui;
  //this->gui_panel = dev_tab->get_panel();

  //---------------------------
}
Command::~Command(){}

//Main function
void Command::run_panel(){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
  ImGui::Begin("Command", NULL, ImGuiWindowFlags_AlwaysAutoResize);

  this->design_panel();

  ImGui::End();
  ImGui::PopStyleColor();

  //---------------------------
}
void Command::design_panel(){
  //---------------------------

  if(ImGui::Button(ICON_FA_PLAY)){
    string command = "firefox -P Dev google.fr";
    int err = system(command.c_str());
  }

  if(ImGui::Button("New editor")){
    static bool truc = true;
    //gui_panel->vec_editor.push_back(new gui::dev::Editor(gui, &truc, "Editor"));
  }

  //---------------------------
}

//Subfunctions

}
