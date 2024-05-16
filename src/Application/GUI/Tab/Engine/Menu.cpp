#include "Menu.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace gui::tab::eng{

//Constructor / Destructor
Menu::Menu(gui::Node* node_gui){
  //---------------------------

  this->node_gui = node_gui;
  this->node_engine = node_gui->get_node_engine();
  this->node_vulkan = node_engine->get_node_vulkan();

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
  if(ImGui::MenuItem("Loader")){
    this->menu_loader();
  }
  if(ImGui::MenuItem(ICON_FA_CAMERA)){
    this->menu_screenshot();
  }
  ImGui::EndMainMenuBar();

  //---------------------------
}

//Subfunction
void Menu::menu_panel(){
  vector<utl::gui::Panel*> vec_panel;
  //---------------------------

  //Node engine panels
  vec_panel = node_engine->get_vec_panel();
  for(int i=0; i<vec_panel.size(); i++){
    utl::gui::Panel* panel = vec_panel[i];
    string title = panel->icon + " " + panel->name;
    ImGui::Checkbox(title.c_str(), &panel->is_open);
  }

  //GUI panels
  vec_panel = node_gui->get_vec_panel();
  for(int i=0; i<vec_panel.size(); i++){
    utl::gui::Panel* panel = vec_panel[i];
    string title = panel->icon + " " + panel->name;
    ImGui::Checkbox(title.c_str(), &panel->is_open);
  }

  //---------------------------
}
void Menu::menu_loader(){
  vector<utl::gui::Panel*> vec_panel = node_engine->get_vec_panel();
  //---------------------------

  for(int i=0; i<vec_panel.size(); i++){
    if(vec_panel[i]->name == "Loader"){
      vec_panel[i]->is_open = !vec_panel[i]->is_open;
    }
  }

  //---------------------------
}
void Menu::menu_screenshot(){
  vk::image::Screenshot* vk_screenshot = node_vulkan->get_vk_screenshot();
  //---------------------------

  vk_screenshot->make_screenshot();

  //---------------------------
}


}
