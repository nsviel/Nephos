#include "Operation.h"

#include <IO/Namespace.h>
#include <Utility/Namespace.h>


namespace io::gui::importer{

//Constructor / Destructor
Operation::Operation(io::gui::importer::Panel* gui_panel){
  //---------------------------

  io::Node* node_io = gui_panel->get_node_io();

  this->io_struct = node_io->get_io_struct();
  this->io_importer = node_io->get_io_importer();
  this->gui_navigator = gui_panel->get_gui_navigator();

  //---------------------------
  this->init_navigator();
}
Operation::~Operation(){}

//Main function
void Operation::init_navigator(){
  utl::gui::Navigator* utl_navigator = gui_navigator->get_utl_navigator();
  //---------------------------

  utl_navigator->add_fct_item_operation([this](utl::base::Path path){this->item_operation(path);});

  //---------------------------
}
void Operation::draw_header(){
  utl::gui::Navigator* utl_navigator = gui_navigator->get_utl_navigator();
  utl::gui::navigator::Structure* nav_struct = utl_navigator->get_nav_struct();
  //---------------------------

  //Load button
  bool condition = (nav_struct->vec_selected_path.size() == 0);
  if(condition) ImGui::BeginDisabled();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Load##222", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
    utl::gui::Navigator* utl_navigator = gui_navigator->get_utl_navigator();
    utl_navigator->make_selection_operation();
  }
  ImGui::PopStyleColor(2);
  if(condition) ImGui::EndDisabled();

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

  // Scale new
  ImGui::SetNextItemWidth(75);
  ImGui::DragFloat("Scale##4567", &io_struct->importer.scaling, 0.1, 0.1, 100, "%.2f x");

  // Remove old
  ImGui::SameLine();
  ImGui::Checkbox("Remove##222", &io_struct->importer.with_clearing);

  // Center new
  ImGui::SameLine();
  ImGui::Checkbox("Centered##222", &io_struct->importer.with_centering);

  //---------------------------
}

//Subfunction
void Operation::item_operation(utl::base::Path utl_path){
  //---------------------------

  std::string path = utl_path.build();
  if(utl::path::is_dir_or_file(path) == "file"){
    io_importer->load_object(utl_path);
  }else{
    io_importer->load_directory(utl_path);
  }

  //---------------------------
}

}
