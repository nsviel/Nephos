#include "Manager.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <iostream>


namespace gui::state{

//Constructor / Destructor
Manager::Manager(gui::Node* node_gui){
  //---------------------------

  this->gui_io = new gui::state::IO(node_gui);

  this->path_default.insert("../media/config/gui/state/default.ini");
  this->path_current = path_default;
  this->path_save = path_default;

  //---------------------------
  this->update_file_list();
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  std::string path_file = path_current.build();
  ImGui::LoadIniSettingsFromDisk(path_file.c_str());

  //---------------------------
}
void Manager::loop(){
  //---------------------------

  this->reload_state();

  //---------------------------
}
void Manager::gui(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "State");

  //Current file
  ImGui::Text("Current");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%s", path_current.filename().c_str());

  if(path_current.name != path_default.name){
    if(ImGui::Button("Make default##state", ImVec2(120, 0))){
      this->make_current_default();
    }
  }

  //Save GUI state
  if(ImGui::Button("Save##state_save", ImVec2(120, 0))){
    ImGui::OpenPopup("state_save_popup");
  }
  if(ImGui::BeginPopup("state_save_popup")){
    ImGui::Text("File name");

    ImGui::SetNextItemWidth(125);
    static char str_n[256];
    strncpy(str_n, path_save.name.c_str(), sizeof(str_n) - 1);
    if(ImGui::InputText("##state_save", str_n, IM_ARRAYSIZE(str_n))){
      path_save.name = str_n;
    }

    if(ImGui::Button("Save##state_save")){
      this->save_state();
      ImGui::CloseCurrentPopup();
    }

    ImGui::EndPopup();
  }

  //Load GUI state
  ImGui::SetNextItemWidth(120);
  int idx = get_idx_path_current();
  std::vector<const char*> vec_file_cchar = utl::casting::vec_str_to_cchar(vec_file);
  if(ImGui::Combo("##imgui_init_states", &idx, vec_file_cchar.data(), vec_file_cchar.size())){
    std::string filename = (std::string)vec_file_cchar[idx];
    this->load_state(filename);
  }

  //---------------------------
}

//Subfunction
void Manager::save_state(){
  //---------------------------

  std::string path_file = path_save.build();
  ImGui::SaveIniSettingsToDisk(path_file.c_str());
  //std::cout<<"[OK] Imgui state saved at "<<path_file<<std::endl;

  this->update_file_list();

  //---------------------------
}
void Manager::load_state(std::string filename){
  if(filename == "") return;
  //---------------------------

  this->path_save.insert_filename(filename);
  this->flag_reload = true;

  //---------------------------
}
void Manager::reload_state(){
  if(!flag_reload) return;
  //---------------------------

  std::string path_file = path_save.build();
  ImGui::LoadIniSettingsFromDisk(path_file.c_str());
  //std::cout<<"[OK] Imgui state reloaded at "<<path_file<<std::endl;
  this->path_current = path_save;

  //---------------------------
  flag_reload = false;
}
void Manager::update_file_list(){
  //---------------------------

  this->vec_file = utl::path::list_all_file(path_current.directory);

  //---------------------------
}
void Manager::make_current_default(){
  //---------------------------

  std::string path_file = path_default.build();
  ImGui::SaveIniSettingsToDisk(path_file.c_str());

  //---------------------------
}
int Manager::get_idx_path_current(){
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
