#include "Exporter.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr::gui{

//Constructor / Destructor
Exporter::Exporter(ldr::Node* node_loader, bool* show_window) : ldr::gui::Navigator(node_loader){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();

  this->dat_graph = node_data->get_dat_graph();
  this->ldr_exporter = node_loader->get_ldr_exporter();

  this->name = "Exporter";
  this->show_window = show_window;
  this->with_bookmark = false;
  this->with_all_format = false;

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(400, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Exporter::design_panel(){
  //---------------------------

  this->draw_header();
  this->draw_navigator();

  //---------------------------
}

//Subfunction
void Exporter::draw_header(){
  //---------------------------

  //Save button
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Save##222", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
    this->item_operation();
    this->vec_selection.clear();
  }
  ImGui::PopStyleColor(2);

  ImGui::BeginTable("header##exporter", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);

  //Actualize current paths
  static std::string file_format;
  static std::string file_name;
  dat::base::Entity* entity = dat_graph->get_selected_entity();
  if(entity != nullptr && file_name != entity->name){
    file_name = entity->name;
    file_format = entity->get_data()->format;
    this->current_path = current_dir + "/" + file_name + "." + file_format;
  }else{
    file_name = utl::path::get_name_from_path(current_path);
    file_format = utl::path::get_format_from_path(current_path);
  }
  static char str_n[256];

  //Directory
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Directory"); ImGui::TableNextColumn();
  strncpy(str_n, current_dir.c_str(), sizeof(str_n) - 1);
  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  if(ImGui::InputText("##exporter_dir", str_n, IM_ARRAYSIZE(str_n))){
    this->current_path = (string)str_n + "/" + file_name + "." + file_format;
  }
  ImGui::PopStyleColor(2);

  //Filename
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Name"); ImGui::TableNextColumn();
  strncpy(str_n, file_name.c_str(), sizeof(str_n) - 1);
  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  if(ImGui::InputText("##exporter_name", str_n, IM_ARRAYSIZE(str_n))){
    this->current_path = current_dir + "/" + (string)str_n + "." + file_format;
  }
  ImGui::PopStyleColor(2);

  //Format
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Format"); ImGui::TableNextColumn();
  static int format = 0;
  std::vector<std::string> vec_format = ldr_exporter->get_supported_format();
  for(int i=0; i<vec_format.size(); i++){
    if(ImGui::RadioButton(vec_format[i].c_str(), &format, i)){
      file_format = vec_format[i];
    }
  }

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Exporter::item_operation(){
  //---------------------------

  dat::base::Entity* entity = dat_graph->get_selected_entity();
  if(entity == nullptr) return;
  
  ldr_exporter->export_entity(entity, current_path);

  //---------------------------
}
bool Exporter::item_format(std::string format){
  //---------------------------

  return ldr_exporter->is_format_supported(format);

  //---------------------------
}

}
