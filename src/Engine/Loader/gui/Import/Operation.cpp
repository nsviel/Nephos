#include "Operation.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>


namespace ldr::gui::importer{

//Constructor / Destructor
Operation::Operation(ldr::gui::importer::Panel* gui_panel){
  //---------------------------

  ldr::Node* node_loader = gui_panel->get_node_loader();

  this->ldr_struct = node_loader->get_ldr_struct();
  this->ldr_importer = node_loader->get_ldr_importer();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::draw_header(){
  //---------------------------

  //Load button
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Load##222", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
    this->item_operation();
  }
  ImGui::PopStyleColor(2);

  // Load button + selected path
  ImGui::BeginTable("header##exporter", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);

  //Selected file path
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Path"); ImGui::TableNextColumn();
  std::string path = ldr_struct->importer.path.build();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", path.c_str());
  ImGui::EndTable();

  // Scale new
  ImGui::SetNextItemWidth(75);
  ImGui::DragFloat("Scale##4567", &ldr_struct->importer.scaling, 0.1, 0.1, 100, "%.2f x");

  // Remove old
  ImGui::SameLine();
  ImGui::Checkbox("Remove##222", &ldr_struct->importer.remove_old);

  // Center new
  ImGui::SameLine();
  ImGui::Checkbox("Centered##222", &ldr_struct->importer.center);

  //---------------------------
}

//Subfunction
void Operation::item_operation(){
  //---------------------------
/*
  //Retrieve all good selected files to load
  std::vector<std::string> vec_path;
  for(int i=0; i<vec_file.size(); i++){
    utl::gui::navigator::File& file = vec_file[i];
    if(vec_selection.contains(file.item.ID)){
      if(ldr_importer->is_format_supported(file.item.format)){
        vec_path.push_back(file.item.path);
      }
    }
  }
  if(vec_path.size() == 0) return;

  //Run all file loading
  for(int i=0; i<vec_path.size(); i++){
    utl::base::Path path;
    path.insert(vec_path[i]);
    ldr_importer->load_object(path);
  }
*/
  //---------------------------
}

}
