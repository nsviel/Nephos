#include "Menu.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>

namespace engine = eng;


namespace gui::tab::eng{

//Constructor / Destructor
Menu::Menu(gui::Node* node_gui){
  //---------------------------

  engine::Node* node_engine = node_gui->get_node_engine();
  cam::Node* node_camera = node_engine->get_node_camera();

  this->node_gui = node_gui;
  this->cam_manager = node_camera->get_cam_manager();

  //---------------------------
}
Menu::~Menu(){}

//Main function
void Menu::draw(){
  //---------------------------

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Panel##111")){
    this->menu_panel();
    ImGui::EndMenu();
  }
  if(ImGui::MenuItem(ICON_FA_DOWNLOAD "##Loader")){
    this->menu_shortcut("Loader");
  }
  if(ImGui::MenuItem(ICON_FA_FLOPPY_DISK "##Exporter")){
    this->menu_shortcut("Exporter");
  }
  if(ImGui::MenuItem(ICON_FA_CAMERA)){
    this->menu_screenshot();
  }
  ImGui::EndMainMenuBar();

  //---------------------------
}

//Subfunction
void Menu::menu_panel(){
  std::vector<utl::gui::Panel*> vec_panel = node_gui->get_vec_panel();
  //---------------------------

  //Node panels
  for(int i=0; i<vec_panel.size(); i++){
    utl::gui::Panel* panel = vec_panel[i];
    std::string title = panel->icon + " " + panel->name;
    ImGui::Checkbox(title.c_str(), &panel->is_open);
  }

  //---------------------------
}
void Menu::menu_shortcut(std::string name){
  std::vector<utl::gui::Panel*> vec_panel = node_gui->get_vec_panel();
  //---------------------------

  for(int i=0; i<vec_panel.size(); i++){
    if(vec_panel[i]->name == name){
      vec_panel[i]->is_open = !vec_panel[i]->is_open;
    }
  }

  //---------------------------
}
void Menu::menu_screenshot(){
  //---------------------------

  cam_manager->make_screenshot();

  //---------------------------
}


}
