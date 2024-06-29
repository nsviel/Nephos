#include "State.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <iostream>


namespace gui::interface{

//Constructor / Destructor
State::State(gui::Node* gui){
  //---------------------------

  this->path.insert("../media/config/gui/default.ini");
  this->vec_file = utl::path::list_all_file(path.directory, ".ini");

  //---------------------------
}
State::~State(){}

//Main function
void State::save_state(){
  //---------------------------

  std::string path = this->path.build();
  ImGui::SaveIniSettingsToDisk(path.c_str());
  std::cout<<"[OK] Imgui docking state saved"<<std::endl;

  //---------------------------
}
void State::load_state(std::string file){
  //---------------------------

  if(file != ""){
    path.filename(file);
  }

  std::string path_file = path.build();
  ImGui::LoadIniSettingsFromDisk(path_file.c_str());

  //---------------------------
}

}
