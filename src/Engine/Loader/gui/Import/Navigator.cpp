#include "Navigator.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>


namespace ldr::gui::importer{

//Constructor / Destructor
Navigator::Navigator(ldr::gui::importer::Panel* gui_panel){
  //---------------------------

  ldr::Node* node_loader = gui_panel->get_node_loader();

  this->ldr_struct = node_loader->get_ldr_struct();
  this->gui_navigator = new ldr::gui::Navigator();

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
    gui_navigator->draw_navigator(ldr_struct->importer.path);
    ImGui::EndTabItem();
  }

  //---------------------------
}


}
