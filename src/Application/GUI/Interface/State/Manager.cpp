#include "Manager.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <iostream>


namespace gui::state{

//Constructor / Destructor
Manager::Manager(gui::Node* node_gui){
  //---------------------------

  this->gui_struct = new gui::state::Structure();
  this->gui_io = new gui::state::IO(gui_struct);

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  std::string default_path = "../media/config/gui/default.json";

  gui_struct->path_default.insert(default_path);
  gui_struct->path_current.insert(default_path);
  gui_struct->path_save.insert(default_path);

  gui_io->state_load(default_path);
  gui_io->update_list_file();

  //---------------------------
}
void Manager::loop(){
  //---------------------------

  if(gui_struct->flag_reload){
    gui_io->state_load(gui_struct->path_save.build());
    gui_io->update_list_file();
    gui_struct->path_current = gui_struct->path_save;
    gui_struct->flag_reload = false;
  }

  //---------------------------
}
void Manager::gui(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "State");

  //Current file
  ImGui::Text("Current");
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(0.5, 1, 0.5, 1), "%s", gui_struct->path_current.filename().c_str());

  if(gui_struct->path_current.name != gui_struct->path_default.name){
    if(ImGui::Button("Make default##state", ImVec2(120, 0))){
      gui_io->make_current_default();
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
    strncpy(str_n, gui_struct->path_save.name.c_str(), sizeof(str_n) - 1);
    if(ImGui::InputText("##state_save", str_n, IM_ARRAYSIZE(str_n))){
      gui_struct->path_save.name = str_n;
    }

    if(ImGui::Button("Save##state_save")){
        std::string path = gui_struct->path_save.build();
      //gui_io->state_save();
      ImGui::CloseCurrentPopup();
    }

    ImGui::EndPopup();
  }

  //Load GUI state
  ImGui::SetNextItemWidth(120);
  int idx = gui_io->get_idx_path_current();
  std::vector<const char*> vec_file_cchar = utl::casting::vec_str_to_cchar(gui_struct->vec_file);
  if(ImGui::Combo("##imgui_init_states", &idx, vec_file_cchar.data(), vec_file_cchar.size())){
    std::string filename = (std::string)vec_file_cchar[idx];
    gui_struct->path_save.insert_filename(filename);
    gui_struct->flag_reload = true;
  }

  //---------------------------
}

//Subfunction


}
