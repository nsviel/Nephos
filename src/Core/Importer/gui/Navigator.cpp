#include "Navigator.h"

#include <Importer/Namespace.h>
#include <Utility/Namespace.h>


namespace io::imp::gui{

//Constructor / Destructor
Navigator::Navigator(io::gui::importer::Panel* gui_panel){
  //---------------------------

  io::Node* node_io = gui_panel->get_node_io();

  this->io_struct = node_io->get_io_struct();
  this->utl_navigator = new utl::gui::Navigator();

  //---------------------------
}
Navigator::~Navigator(){}

//Main function
void Navigator::draw_tab(int width){
  //---------------------------

  //Flag to force navigator tab in case of bookmark folder
  ImGuiTabItemFlags flag = 0;
  if(open_tab){
    flag = ImGuiTabItemFlags_SetSelected;
    this->open_tab = false;
  }

  ImGui::SetNextItemWidth(width);
  if(ImGui::BeginTabItem("Navigator##50", NULL, flag)){
    utl_navigator->draw_navigator(io_struct->importer.path);
    ImGui::EndTabItem();
  }

  //---------------------------
}


}
