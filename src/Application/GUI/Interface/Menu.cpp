#include "Menu.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace gui::interface{

//Constructor / Destructor
Menu::Menu(gui::Node* node_gui){
  //---------------------------

  this->gui_struct = node_gui->get_gui_struct();
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
    //Demo window
    ImGui::Checkbox("Demo window", &gui_struct->show_demo);

    //Demo file
    if(ImGui::Button("Demo file", ImVec2(120, 0))){
      int ret = system("xed ../extern/imgui/core/imgui_demo.cpp");
    }

    //Save docking state
    if(ImGui::Button("Save dock state", ImVec2(120, 0))){
      gui_state->save_state();
    }

    ImGui::EndMenu();
  }

  if(gui_struct->show_demo){
    ImGui::ShowDemoWindow(&gui_struct->show_demo);
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
