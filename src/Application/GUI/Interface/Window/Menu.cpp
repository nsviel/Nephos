#include "Menu.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace gui::interface{

//Constructor / Destructor
Menu::Menu(gui::Node* node_gui){
  //---------------------------

  this->gui_demo = node_gui->get_gui_demo();
  this->gui_font = node_gui->get_gui_font();
  this->gui_git = new utl::element::gui::Git();
  this->gui_state = node_gui->get_gui_state();

  //---------------------------
}
Menu::~Menu(){}

//Menu function
void Menu::menu(){
  //---------------------------

  //this->menu_option();
  this->menu_imgui();
  this->menu_git();

  //---------------------------
}

//Subfunction
void Menu::menu_option(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(ImGui::BeginMenu(ICON_FA_GEAR, "menu_option")){
    gui_font->combo_font_gui();
    gui_font->combo_font_editor();
    ImGui::EndMenu();
  }

  //---------------------------
}
void Menu::menu_imgui(){
  //---------------------------

  if(ImGui::BeginMenu(ICON_FA_BOOK, "menu_imgui")){
    gui_demo->gui();
    gui_state->gui();

    ImGui::EndMenu();
  }

  //---------------------------
}
void Menu::menu_git(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(ImGui::BeginMenu(ICON_FA_GEAR, "menu_git")){
    gui_git->design_panel();

    ImGui::EndMenu();
  }

  //---------------------------
}

}
