#include "Loader.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <nlohmann/json.hpp>
#include <iostream>


namespace gui::state{

//Constructor / Destructor
Loader::Loader(gui::state::Structure* gui_struct){
  //---------------------------

  this->gui_struct = gui_struct;

  //---------------------------
}
Loader::~Loader(){}

//Main function
void Loader::load_state(std::string path){
  //---------------------------

  nlohmann::json j;
  this->open_json(j);
  this->extract_ini_settings(j);

  //---------------------------
}

//Subfunction
void Loader::open_json(nlohmann::json& j){
  //---------------------------

  std::ifstream file(path.c_str());
  if(file.is_open()){
    nlohmann::json j;
    file >> j;
    file.close();
  }else{
    std::cerr << "[error] Failed to open file for loading settings: " << path << std::endl;
  }

  //---------------------------
}
void Loader::extract_ini_settings(nlohmann::json& j){
  //---------------------------

  if(j.contains("imgui_settings")){
    std::string settings = j["imgui_settings"];
    ImGui::LoadIniSettingsFromMemory(settings.c_str(), settings.size());
  }else{
    std::cerr << "[error] JSON does not contain 'imgui_settings' key." << std::endl;
  }

  //---------------------------
}

}
