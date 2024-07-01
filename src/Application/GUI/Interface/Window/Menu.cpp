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
    this->menu_demo();
    this->menu_state();

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

//Subfunction
void Menu::menu_demo(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Demo");

  //Demo window
  bool* show_demo = gui_demo->get_show_demo();
  ImGui::Checkbox("Window", show_demo);

  //Demo file
  if(ImGui::Button("Open file", ImVec2(120, 0))){
    gui_demo->open_demo_file();
  }

  //---------------------------
  ImGui::Separator();
}
void Menu::menu_state(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "State");

  //Data
  std::vector<std::string> vec_file = gui_state->get_vec_file();
  utl::base::Path* path_current = gui_state->get_path_current();
  utl::base::Path* path_save = gui_state->get_path_save();

  //Current file
  ImGui::Text("Current");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%s", path_current->filename().c_str());

  if(gui_state->get_is_default() == false){
    if(ImGui::Button("Make default##state", ImVec2(120, 0))){
      gui_state->make_current_default();
    }
  }

  //Save GUI state
  if(ImGui::Button("Save##state_save", ImVec2(120, 0))){
    ImGui::OpenPopup("state_save_popup");
  }
  if(ImGui::BeginPopup("state_save_popup")){
    ImGui::Text("File name");

    ImGui::SetNextItemWidth(125);
    static char str_n[256];
    strncpy(str_n, path_save->name.c_str(), sizeof(str_n) - 1);
    if(ImGui::InputText("##state_save", str_n, IM_ARRAYSIZE(str_n))){
      path_save->name = str_n;
    }

    if(ImGui::Button("Save##state_save")){
      gui_state->save_state();
      ImGui::CloseCurrentPopup();
    }

    ImGui::EndPopup();
  }

  //Load GUI state
  ImGui::SetNextItemWidth(120);
  int idx = gui_state->get_idx_path_current();
  std::vector<const char*> vec_file_cchar = utl::casting::vec_str_to_cchar(vec_file);
  if(ImGui::Combo("##imgui_init_states", &idx, vec_file_cchar.data(), vec_file_cchar.size())){
    std::string filename = (std::string)vec_file_cchar[idx];
    gui_state->load_state(filename);
  }

  //---------------------------
}

}
