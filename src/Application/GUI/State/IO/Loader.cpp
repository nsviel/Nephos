#include "Loader.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>


namespace gui::state{

//Constructor / Destructor
Loader::Loader(gui::state::Manager* manager){
  //---------------------------

  this->node_gui = manager->get_node_gui();
  this->sta_struct = manager->get_sta_struct();

  //---------------------------
}
Loader::~Loader(){}

//Main function
void Loader::load_state(std::string path){
  //---------------------------

  this->read_ini_settings(path);
  this->read_panel(path);

  //---------------------------
}

//Subfunction
void Loader::read_ini_settings(std::string& path){
  //---------------------------

  std::string settings = utl::json::read_value<std::string>(path, "imgui_settings");
  ImGui::LoadIniSettingsFromMemory(settings.c_str(), settings.size());

  //---------------------------
}
void Loader::read_panel(std::string& path){
  std::vector<utl::gui::Panel*> vec_panel = node_gui->get_vec_panel();
  //---------------------------

  for(auto& panel : vec_panel){
    std::string key = "panel." + panel->name;
    utl::json::read_value(path, key, panel->is_open);
  }

  //---------------------------
}

}
