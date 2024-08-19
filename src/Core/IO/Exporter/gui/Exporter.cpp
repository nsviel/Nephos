#include "Exporter.h"

#include <IO/Exporter/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io::exp::gui{

//Constructor / Destructor
Exporter::Exporter(io::exp::Node* node_exporter){
  //---------------------------

  dat::Node* node_data = node_exporter->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();

  this->io_struct = node_exporter->get_io_struct();
  this->io_exporter = node_exporter->get_io_exporter();
  this->dat_selection = node_graph->get_dat_selection();

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::draw_header(utl::base::Element* element){
  //---------------------------

  this->item_update(element);

  this->display_action();
  this->display_path(element);
  this->display_format();
  this->display_encording();
  this->display_option();

  //---------------------------
  ImGui::Separator();
}

//Header function
void Exporter::display_action(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  if(entity == nullptr) return;
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));

  if(io_exporter->is_current_config(entity)){
    if(ImGui::Button("Save##444", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
      this->item_operation(entity);
    }
  }else{
    if(ImGui::Button("Export##444", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
      this->item_operation(entity);
    }
  }

  ImGui::PopStyleColor(2);

  //---------------------------
}
void Exporter::display_path(utl::base::Element* element){
  //---------------------------

  ImGui::BeginTable("header##exporter", 3);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);
  ImGui::TableSetupColumn("3", ImGuiTableColumnFlags_WidthFixed, 25.0f);

  //Directory
  static char str_n[256];
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Directory"); ImGui::TableNextColumn();
  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
  std::string current_path = io_struct->path.directory;
  if(current_path == "") current_path = "(not defined)";
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", current_path.c_str());
  ImGui::PopStyleColor();
  ImGui::TableNextColumn();
  if(ImGui::Button(ICON_FA_FOLDER "##folder_path")){
    utl::directory::open(io_struct->path.directory);
  }

  //Filename
  if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Name"); ImGui::TableNextColumn();
    strncpy(str_n, io_struct->path.name.c_str(), sizeof(str_n) - 1);
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
    if(ImGui::InputText("##exporter_name", str_n, IM_ARRAYSIZE(str_n))){
      io_struct->path.name = (std::string)str_n;
    }
    ImGui::PopStyleColor(2);
  }

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
  std::vector<std::string> vec_format = io_exporter->get_supported_format();
  for(int i=0; i<vec_format.size(); i++){
    if(ImGui::RadioButton(vec_format[i].c_str(), &format, i)){
      io_struct->path.format = vec_format[i];
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

  std::vector<io::exp::Encoding> vec_encoding = io_exporter->get_supported_encoding(io_struct->path.format);
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Encoding"); ImGui::TableNextColumn();
  static int mode = 1;
  bool condition = (std::find(vec_encoding.begin(), vec_encoding.end(), io::exp::ASCII) == vec_encoding.end());
  if(condition){
    ImGui::BeginDisabled();
    mode = io::exp::BINARY;
  }
  if(ImGui::RadioButton("ASCII", &mode, io::exp::ASCII)){
    io_struct->encoding = io::exp::ASCII;
  }
  if(condition) ImGui::EndDisabled();
  ImGui::SameLine();
  condition = (std::find(vec_encoding.begin(), vec_encoding.end(), io::exp::BINARY) == vec_encoding.end());
  if(condition){
    ImGui::BeginDisabled();
    mode = io::exp::ASCII;
  }
  if(ImGui::RadioButton("Binary", &mode, io::exp::BINARY)){
    io_struct->encoding = io::exp::BINARY;
  }
  if(condition) ImGui::EndDisabled();

  ImGui::EndTable();

  //---------------------------
}
void Exporter::display_option(){
  //---------------------------

  ImGui::Checkbox("Apply transformation##3", &io_struct->with_transformation);
  ImGui::SameLine();
  ImGui::Checkbox("Current colorization##3", &io_struct->with_colorization);

  //---------------------------
}

//Subfunction
void Exporter::item_filtering(std::vector<std::string>& vec_path){
  std::vector<std::string> vec_format = io_exporter->get_supported_format();
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
void Exporter::item_update(utl::base::Element* element){
  dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element);
  //---------------------------

  //Actualize current name
  if(entity != nullptr && io_struct->path.name != entity->name){
    utl::base::Data* data = &entity->data;
    io_struct->path.name = entity->name;

    if(io_exporter->is_format_supported(data->path.format)){
      io_struct->path.format = data->path.format;
    }
  }

  //---------------------------
}
void Exporter::item_operation(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  std::string format = (io_struct->path.format != "-") ? io_struct->path.format : "";

  utl::base::Data* data = &entity->data;
  data->name = io_struct->path.name;
  data->path.directory = io_struct->path.directory;
  data->path.name = data->name;
  data->path.format = format;

  io_exporter->export_entity(entity, data->path.build());

  //---------------------------
}

}
