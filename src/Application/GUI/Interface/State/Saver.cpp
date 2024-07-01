#include "Saver.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>


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

  nlohmann::json j;
  this->build_json_ini_settings(j);
  this->dump_json(j, path);

  //---------------------------
}

//Subfunction
void Saver::build_json_ini_settings(nlohmann::json& j){
  //---------------------------

  size_t size;
  const char* settings = ImGui::SaveIniSettingsToMemory(&size);
  j["imgui_settings"] = std::string(settings, size);

  //---------------------------
}
void Saver::dump_json(nlohmann::json& j, std::string path){
  //---------------------------

  std::ofstream file(path.c_str());
  if(file.is_open()){
    file << j.dump(4);  // Pretty print with 4 spaces indentation
    file.close();
  }else{
    std::cerr << "[error] Failed to open file for saving settings: " << path << std::endl;
  }

  //---------------------------
}

}
