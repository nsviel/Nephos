#include "State.h"

#include <GUI/Namespace.h>
#include <imgui/core/imgui.h>
#include <iostream>


namespace gui::interface{

//Constructor / Destructor
State::State(gui::Node* gui){
  //---------------------------


  //---------------------------
}
State::~State(){}

//Main function
void State::dock_save_state(){
  //---------------------------

  ImGui::SaveIniSettingsToDisk("../media/config/gui/imgui.ini");
  std::cout<<"[OK] Imgui docking state saved"<<std::endl;

  //---------------------------
}
void State::dock_load_state(){
  //---------------------------

  ImGui::LoadIniSettingsFromDisk("../media/config/gui/imgui.ini");

  //---------------------------
}

}
