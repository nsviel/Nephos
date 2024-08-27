#include "Header.h"

#include <IO/Importer/Namespace.h>
#include <Utility/Namespace.h>


namespace io::imp::gui{

//Constructor / Destructor
Header::Header(io::imp::gui::Panel* gui_panel){
  //---------------------------

  io::imp::Node* node_importer = gui_panel->get_node_importer();

  this->io_struct = node_importer->get_io_struct();
  this->utl_navigator = gui_panel->get_utl_navigator();
  this->nav_struct = utl_navigator->get_nav_struct();

  //---------------------------
}
Header::~Header(){}

//Main function
void Header::draw_header(){
  //---------------------------

  this->draw_loader();
  //this->draw_path();
  this->draw_operation();

  //---------------------------
}

//Subfunction
void Header::draw_loader(){
  //---------------------------

  //Load button
  bool condition = (nav_struct->vec_selected_path.size() == 0);
  if(condition) ImGui::BeginDisabled();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Load##222", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
    utl_navigator->make_selection_operation();
  }
  ImGui::PopStyleColor(2);
  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Header::draw_path(){
  //---------------------------

  //Selected file paths
  if(nav_struct->vec_selected_path.size() != 0){
    ImGui::BeginTable("header##exporter", 2);
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);
    ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Path"); ImGui::TableNextColumn();
    for(int i=0; i<nav_struct->vec_selected_path.size(); i++){
      std::string& path = nav_struct->vec_selected_path[i];
      ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", path.c_str());
      ImGui::TableNextRow(); ImGui::TableNextColumn(); ImGui::TableNextColumn();
    }
    ImGui::EndTable();
  }

  //---------------------------
}
void Header::draw_operation(){
  //---------------------------

  // Scale new
  ImGui::SetNextItemWidth(75);
  ImGui::DragFloat("Scale##4567", &io_struct->scaling, 0.1, 0.1, 100, "%.2f x");

  // Remove old
  ImGui::SameLine();
  ImGui::Checkbox("Remove##222", &io_struct->with_clearing);

  // Center new
  ImGui::SameLine();
  ImGui::Checkbox("Centered##222", &io_struct->with_centering);

  //---------------------------
}

}
