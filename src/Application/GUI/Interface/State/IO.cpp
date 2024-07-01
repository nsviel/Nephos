#include "IO.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <nlohmann/json.hpp>
#include <iostream>


namespace gui::state{

//Constructor / Destructor
IO::IO(gui::Node* gui){
  //---------------------------

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

}
