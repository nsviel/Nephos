#include "State.h"

#include <GUI/Namespace.h>
#include <imgui/core/imgui.h>
#include <iostream>


namespace gui::interface{

//Constructor / Destructor
State::State(gui::Node* gui){
  //---------------------------

  this->current = "../media/config/gui/imgui.ini";

  //---------------------------
}
State::~State(){}

//Main function
void State::dock_save_state(){
  //---------------------------

  ImGui::SaveIniSettingsToDisk(current.c_str());
  std::cout<<"[OK] Imgui docking state saved"<<std::endl;

  //---------------------------
}
void State::dock_load_state(){
  //---------------------------

  ImGui::LoadIniSettingsFromDisk(current.c_str());

  //---------------------------
}

}
