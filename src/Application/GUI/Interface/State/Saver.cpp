#include "Saver.h"

#include <GUI/Namespace.h>
#include <Utility/Function/File/Json.h>


namespace gui::state{

//Constructor / Destructor
Saver::Saver(gui::state::Manager* manager){
  //---------------------------

  this->node_gui = manager->get_node_gui();
  this->sta_struct = manager->get_sta_struct();

  //---------------------------
}
Saver::~Saver(){}

//Main function
void Saver::save_state(){
  //---------------------------

  std::string path = sta_struct->path_save.build();
  this->write_ini_settings(path);
  this->write_panel(path);

  //---------------------------
}

//Subfunction
void Saver::write_ini_settings(std::string& path){
  //---------------------------

  size_t size;
  const char* settings = ImGui::SaveIniSettingsToMemory(&size);
  utl::json::write_value(path, "imgui_settings", std::string(settings, size));

  //---------------------------
}
void Saver::write_panel(std::string& path){
  std::vector<utl::gui::Panel*> vec_panel = node_gui->get_vec_panel();
  //---------------------------

  for(int i=0; i<vec_panel.size(); i++){
    utl::gui::Panel* panel = vec_panel[i];

    std::string key = "panel." + panel->name;
    utl::json::write_value(path, key, panel->is_open);
  }

  //---------------------------
}

}
