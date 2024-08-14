#include "Navigator.h"

#include <Importer/Namespace.h>
#include <Utility/Namespace.h>


namespace io::imp::gui{

//Constructor / Destructor
Navigator::Navigator(io::imp::gui::Panel* gui_panel){
  //---------------------------

  io::imp::Node* node_importer = gui_panel->get_node_importer();

  this->io_struct = node_importer->get_io_struct();
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
    utl_navigator->draw_navigator(io_struct->path);
    ImGui::EndTabItem();
  }

  //---------------------------
}


}
