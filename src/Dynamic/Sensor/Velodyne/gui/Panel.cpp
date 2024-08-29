#include "Panel.h"

#include <Velodyne/Namespace.h>


namespace vld::gui{

//Constructor / Destructor
Panel::Panel(vld::Node* node_velodyne, bool* show_window){
  //---------------------------

  this->vld_struct = node_velodyne->get_vld_struct();
  this->gui_player = new vld::gui::Player(node_velodyne);
  this->gui_server = new vld::gui::Server(node_velodyne);

  this->show_window = show_window;
  this->name = "Velodyne";

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  //---------------------------

  gui_player->design_player();
  gui_server->design_server();

  //---------------------------
}

}
