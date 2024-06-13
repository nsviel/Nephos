#include "Exporter.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ldr::gui::exporter{

//Constructor / Destructor
Exporter::Exporter(ldr::Node* node_loader){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();

  this->ldr_struct = node_loader->get_ldr_struct();
  this->dat_selection = node_data->get_dat_selection();
  this->ldr_exporter = node_loader->get_ldr_exporter();

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::draw_header(dat::base::Entity* entity){
  //---------------------------

  this->item_update(entity);

  this->display_action();
  this->display_path();
  this->display_format();
  this->display_encording();
  this->display_option();

  //---------------------------
  ImGui::Separator();
}

//Header function
void Exporter::display_action(){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Save##444", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
    this->item_operation();
  }
  ImGui::PopStyleColor(2);

  //---------------------------
}
void Exporter::display_path(){
  //---------------------------

  ImGui::BeginTable("header##exporter", 3);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);
  ImGui::TableSetupColumn("3", ImGuiTableColumnFlags_WidthFixed, 20.0f);

  //Directory
  static char str_n[256];
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Directory"); ImGui::TableNextColumn();
  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
  std::string current_path = ldr_struct->current_dir;
  if(current_path == "") current_path = "(not defined)";
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", current_path.c_str());
  ImGui::PopStyleColor();
  ImGui::TableNextColumn();
  if(ImGui::Button(ICON_FA_FOLDER "##folder_path")){
    utl::directory::open(ldr_struct->current_dir);
  }

  //Filename
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Name"); ImGui::TableNextColumn();
  strncpy(str_n, ldr_struct->current_name.c_str(), sizeof(str_n) - 1);
  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  if(ImGui::InputText("##exporter_name", str_n, IM_ARRAYSIZE(str_n))){
    ldr_struct->current_name = (string)str_n;
  }
  ImGui::PopStyleColor(2);

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Exporter::display_format(){
  //---------------------------

  ImGui::BeginTable("header##exporter", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Format"); ImGui::TableNextColumn();
  static int format = 0;
  std::vector<std::string> vec_format = ldr_exporter->get_supported_format();
  for(int i=0; i<vec_format.size(); i++){
    if(ImGui::RadioButton(vec_format[i].c_str(), &format, i)){
      ldr_struct->current_format = vec_format[i];
    }
  }

  ImGui::EndTable();

  //---------------------------
}
void Exporter::display_encording(){
  //---------------------------

  ImGui::BeginTable("header##exporter", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);

  std::vector<int> vec_encoding = ldr_exporter->get_supported_encoding(ldr_struct->current_format);
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Encoding"); ImGui::TableNextColumn();
  static int mode = 1;
  bool condition = (std::find(vec_encoding.begin(), vec_encoding.end(), ldr::io::ASCII) == vec_encoding.end());
  if(condition){
    ImGui::BeginDisabled();
    mode = ldr::io::BINARY;
  }
  if(ImGui::RadioButton("ASCII", &mode, ldr::io::ASCII)){
    ldr_struct->exporter.encoding = ldr::io::ASCII;
  }
  if(condition) ImGui::EndDisabled();
  ImGui::SameLine();
  condition = (std::find(vec_encoding.begin(), vec_encoding.end(), ldr::io::BINARY) == vec_encoding.end());
  if(condition){
    ImGui::BeginDisabled();
    mode = ldr::io::ASCII;
  }
  if(ImGui::RadioButton("Binary", &mode, ldr::io::BINARY)){
    ldr_struct->exporter.encoding = ldr::io::BINARY;
  }
  if(condition) ImGui::EndDisabled();

  ImGui::EndTable();

  //---------------------------
}
void Exporter::display_option(){
  //---------------------------

  ImGui::Checkbox("Transformed##3", &ldr_struct->exporter.transformed);

  //---------------------------
}

//Subfunction
void Exporter::item_filtering(std::vector<std::string>& vec_path){
  std::vector<std::string> vec_format = ldr_exporter->get_supported_format();
  //---------------------------

  std::vector<std::string> vec_path_ok;
  for(int i=0; i<vec_path.size(); i++){
    std::string& path = vec_path[i];

    //If direcctory, ok
    if(utl::directory::is_directory(path)){
      vec_path_ok.push_back(path);
      continue;
    }

    //If file, check format compatibility
    std::string format = utl::path::get_format_from_path(path);
    if(format == "-") continue;
    for(int j=0; j<vec_format.size(); j++){
      if(format == vec_format[j]){
        vec_path_ok.push_back(path);
        break;
      }
    }

  }

  //---------------------------
  vec_path = vec_path_ok;
}
void Exporter::item_update(dat::base::Entity* entity){
  //---------------------------

  //Actualize current name
  if(entity != nullptr && ldr_struct->current_name != entity->name){
    utl::base::Data* data = &entity->data;
    ldr_struct->current_name = entity->name;

    if(ldr_exporter->is_format_supported(data->format)){
      ldr_struct->current_format = data->format;
    }
  }

  //---------------------------
}
void Exporter::item_operation(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  if(entity == nullptr) return;
  //---------------------------

  std::string format = (ldr_struct->current_format != "-") ? ldr_struct->current_format : "";

  utl::base::Data* data = &entity->data;
  data->name = ldr_struct->current_name;
  data->format = format;
  data->path.directory = ldr_struct->current_dir;
  data->path.data = ldr_struct->get_current_path();

  ldr_exporter->export_entity(entity, data->path.data);

  //---------------------------
}

}
