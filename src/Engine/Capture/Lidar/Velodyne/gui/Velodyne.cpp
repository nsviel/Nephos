#include "Velodyne.h"

#include <Velodyne/Namespace.h>
#include <Utility/Namespace.h>
#include <Graph/Namespace.h>


namespace vld::gui{

//Constructor / Destructor
Velodyne::Velodyne(vld::structure::Main* vld_struct, bool* show_window){
  //---------------------------

  this->vld_struct = vld_struct;
  this->gui_player = new vld::gui::Player(vld_struct);
  this->gui_server = new vld::gui::Server(vld_struct);

  this->show_window = show_window;
  this->name = "Velodyne";

  //---------------------------
}
Velodyne::~Velodyne(){}

//Main function
void Velodyne::run_panel(){
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
void Velodyne::design_panel(){
  //---------------------------

  gui_player->design_player();
  gui_server->design_server();

  //---------------------------
}

}
