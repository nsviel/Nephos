#include "Saver.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <nlohmann/json.hpp>
#include <iostream>


namespace gui::state{

//Constructor / Destructor
Saver::Saver(gui::state::Structure* gui_struct){
  //---------------------------

  this->gui_struct = gui_struct;

  //---------------------------
}
Saver::~Saver(){}

//Main function
void Saver::save_state(std::string path){
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

//Subfunction


}
