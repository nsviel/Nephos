#include "Recorder.h"

#include <IO/Exporter/Namespace.h>
#include <Data/Namespace.h>
#include <Data/Player/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io::exp::gui{

//Constructor / Destructor
Recorder::Recorder(io::exp::Node* node_exporter){
  //---------------------------

  dat::Node* node_data = node_exporter->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::ply::Node* node_player = node_data->get_node_player();

  this->ply_button = node_player->get_ply_button();
  this->io_struct = node_exporter->get_io_struct();
  this->gph_selection = node_graph->get_gph_selection();

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::draw_header(std::shared_ptr<utl::base::Element> element){
  std::shared_ptr<dat::base::Sensor> sensor = std::dynamic_pointer_cast<dat::base::Sensor>(element);
  //---------------------------

  this->item_update(sensor);

  this->display_action(sensor);
  this->display_path();
  this->display_format();

  //---------------------------
  ImGui::Separator();
}

//Header function
void Recorder::display_action(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  if(!sensor->state.record){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Record##444", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
      ply_button->button_record();
      this->item_operation(sensor);
    }
    ImGui::PopStyleColor(2);
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(120, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(150, 50, 50, 255));
    if(ImGui::Button("Stop##444", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
      ply_button->button_record();
      this->item_operation(sensor);
    }
    ImGui::PopStyleColor(2);
  }

  //---------------------------
}
void Recorder::display_path(){
  //---------------------------

  ImGui::BeginTable("header##recorder", 3);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);
  ImGui::TableSetupColumn("3", ImGuiTableColumnFlags_WidthFixed, 20.0f);

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

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Recorder::display_format(){
  //---------------------------

  ImGui::BeginTable("header##exporter", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Format"); ImGui::TableNextColumn();
  static int format = 0;
  for(int i=0; i<vec_format.size(); i++){
    if(ImGui::RadioButton(vec_format[i].c_str(), &format, i)){
      io_struct->path.format = vec_format[i];
    }
  }

  ImGui::EndTable();

  //---------------------------
}

//Subfunction
void Recorder::item_filtering(std::vector<std::string>& vec_path){
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
        vec_path_ok.push_back(vec_path[i]);
        break;
      }

    }
  }

  //---------------------------
  vec_path = vec_path_ok;
}
void Recorder::item_update(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  //Actualize current name
  if(sensor != nullptr && io_struct->path.name != sensor->name){
    utl::base::Data& data = *sensor->data;
    io_struct->path.name = sensor->name;

    this->vec_format.clear();
    for(int i=0; i<sensor->info.vec_recorder.size(); i++){
      this->vec_format.push_back(sensor->info.vec_recorder[i]->format);
    }
  }

  //---------------------------
}
void Recorder::item_operation(std::shared_ptr<dat::base::Entity> entity){
  if(!entity) return;
  //---------------------------

  std::string format = (io_struct->path.format != "-") ? io_struct->path.format : "";

  utl::base::Data& data = *entity->data;
  data.name = io_struct->path.name;
  data.path.directory = io_struct->path.directory;
  data.path.name = data.name;
  data.path.format = format;

  //---------------------------
}

}
