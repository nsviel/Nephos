#include "State.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <iostream>


namespace gui::interface{

//Constructor / Destructor
State::State(gui::Node* gui){
  //---------------------------

  this->path.insert("../media/config/gui/state/default.ini");

  //---------------------------
  this->update_file_list();
}
State::~State(){}

//Main function
void State::save_state(){
  //---------------------------

  std::string path_file = path.build();
  ImGui::SaveIniSettingsToDisk(path_file.c_str());
  std::cout<<"[OK] Imgui state saved at "<<path_file<<std::endl;

  this->update_file_list();

  //---------------------------
}
void State::load_state(std::string filename){
  //---------------------------

  if(filename != ""){
    path.filename(filename);
  }

  std::string path_file = path.build();
  ImGui::LoadIniSettingsFromDisk(path_file.c_str());
  //std::cout<<"[OK] Imgui load state at "<<path_file<<std::endl;

  //---------------------------
}

//Subfunction
void State::update_file_list(){
  //---------------------------

  this->vec_file = utl::path::list_all_file(path.directory);

  //---------------------------
}

}
