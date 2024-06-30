#include "State.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <iostream>


namespace gui::interface{

//Constructor / Destructor
State::State(gui::Node* gui){
  //---------------------------

  this->current_path.insert("../media/config/gui/state/default.ini");
  this->save_path = current_path;

  //---------------------------
  this->update_file_list();
}
State::~State(){}

//Main function
void State::init(){
  //---------------------------

  std::string path_file = current_path.build();
  ImGui::LoadIniSettingsFromDisk(path_file.c_str());

  //---------------------------
}

//Subfunction
void State::save_state(){
  //---------------------------

  std::string path_file = save_path.build();
  ImGui::SaveIniSettingsToDisk(path_file.c_str());
  //std::cout<<"[OK] Imgui state saved at "<<path_file<<std::endl;

  this->update_file_list();

  //---------------------------
}
void State::load_state(std::string filename){
  if(filename == "") return;
  //---------------------------

  this->save_path.insert_filename(filename);
  this->flag_reload = true;

  //---------------------------
}
void State::reload_state(){
  if(!flag_reload) return;
  //---------------------------

  std::string path_file = save_path.build();
  ImGui::LoadIniSettingsFromDisk(path_file.c_str());
  //std::cout<<"[OK] Imgui state reloaded at "<<path_file<<std::endl;
  this->current_path = save_path;

  //---------------------------
  flag_reload = false;
}
void State::update_file_list(){
  //---------------------------

  this->vec_file = utl::path::list_all_file(current_path.directory);

  //---------------------------
}
int State::get_idx_current_path(){
  int idx = -1;
  //---------------------------

  for(int i=0; i<vec_file.size(); i++){
    std::string& filename = vec_file[i];
    if(current_path.filename() == filename){
      return i;
    }
  }

  //---------------------------
  return idx;
}

}
