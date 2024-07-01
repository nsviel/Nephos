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


}
