#include "IO.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <nlohmann/json.hpp>
#include <iostream>


namespace gui::state{

//Constructor / Destructor
IO::IO(gui::state::Structure* gui_struct){
  //---------------------------

  this->gui_struct = gui_struct;

  //---------------------------
}
IO::~IO(){}

//Main function
void IO::state_save(std::string path){
  //---------------------------

  size_t size;
  const char* settings = ImGui::SaveIniSettingsToMemory(&size);
  nlohmann::json j;
  j["imgui_settings"] = std::string(settings, size);

  std::ofstream file(path.c_str());
  if(file.is_open()){
    file << j.dump(4);  // Pretty print with 4 spaces indentation
    file.close();
  }else{
    std::cerr << "Failed to open file for saving settings: " << path << std::endl;
  }

  //---------------------------
}
void IO::state_load(std::string path){
  //---------------------------

  std::ifstream file(path.c_str());
  if(file.is_open()){
    nlohmann::json j;
    file >> j;
    file.close();

    if(j.contains("imgui_settings")){
      std::string settings = j["imgui_settings"];
      ImGui::LoadIniSettingsFromMemory(settings.c_str(), settings.size());
    }else{
      std::cerr << "JSON does not contain 'imgui_settings' key." << std::endl;
    }
  }else{
    std::cerr << "Failed to open file for loading settings: " << path << std::endl;
  }

  //---------------------------
}

//Subfunction
void IO::update_list_file(){
  //---------------------------

  gui_struct->vec_file = utl::path::list_all_file(gui_struct->path_current.directory);

  //---------------------------
}
void IO::make_current_default(){
  //---------------------------

  std::string path = gui_struct->path_default.build();
  //gui_io->state_save();

  //---------------------------
}
int IO::get_idx_path_current(){
  int idx = -1;
  //---------------------------

  for(int i=0; i<gui_struct->vec_file.size(); i++){
    std::string& filename = gui_struct->vec_file[i];
    if(gui_struct->path_current.filename() == filename){
      return i;
    }
  }

  //---------------------------
  return idx;
}

}
