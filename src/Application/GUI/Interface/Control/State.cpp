#include "State.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <iostream>


namespace gui::interface{

//Constructor / Destructor
State::State(gui::Node* gui){
  //---------------------------

  this->path_default.insert("../media/config/gui/state/default.ini");
  this->path_current = path_default;
  this->path_save = path_default;

  //---------------------------
  this->update_file_list();
}
State::~State(){}

//Main function
void State::init(){
  //---------------------------

  std::string path_file = path_current.build();
  ImGui::LoadIniSettingsFromDisk(path_file.c_str());

  //---------------------------
}
void State::loop(){
  //---------------------------

  this->reload_state();

  //---------------------------
}

//Subfunction
void State::save_state(){
  //---------------------------

  std::string path_file = path_save.build();
  ImGui::SaveIniSettingsToDisk(path_file.c_str());
  //std::cout<<"[OK] Imgui state saved at "<<path_file<<std::endl;

  this->update_file_list();

  //---------------------------
}
void State::load_state(std::string filename){
  if(filename == "") return;
  //---------------------------

  this->path_save.insert_filename(filename);
  this->flag_reload = true;

  //---------------------------
}
void State::reload_state(){
  if(!flag_reload) return;
  //---------------------------

  std::string path_file = path_save.build();
  ImGui::LoadIniSettingsFromDisk(path_file.c_str());
  //std::cout<<"[OK] Imgui state reloaded at "<<path_file<<std::endl;
  this->path_current = path_save;

  //---------------------------
  flag_reload = false;
}
void State::update_file_list(){
  //---------------------------

  this->vec_file = utl::path::list_all_file(path_current.directory);

  //---------------------------
}
void State::make_current_default(){
  //---------------------------

  std::string path_file = path_default.build();
  ImGui::SaveIniSettingsToDisk(path_file.c_str());

  //---------------------------
}
int State::get_idx_path_current(){
  int idx = -1;
  //---------------------------

  for(int i=0; i<vec_file.size(); i++){
    std::string& filename = vec_file[i];
    if(path_current.filename() == filename){
      return i;
    }
  }

  //---------------------------
  return idx;
}

}
