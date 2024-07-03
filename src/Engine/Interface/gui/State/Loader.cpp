#include "Loader.h"

#include <Interface/Namespace.h>
#include <Utility/Namespace.h>


namespace itf::state{

//Constructor / Destructor
Loader::Loader(itf::state::Manager* manager){
  //---------------------------

  this->node_interface = manager->get_node_interface();
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
  std::vector<utl::gui::Panel*> vec_panel = node_interface->get_vec_panel();
  //---------------------------

  for(int i=0; i<vec_panel.size(); i++){
    utl::gui::Panel* panel = vec_panel[i];

    std::string key = "panel." + panel->name;
    utl::json::read_value(path, key, panel->is_open);
  }

  //---------------------------
}

}
