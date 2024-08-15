#include "Recorder.h"

#include <Exporter/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io::exp::gui{

//Constructor / Destructor
Recorder::Recorder(io::exp::Node* node_exporter){
  //---------------------------

  dat::Node* node_data = node_exporter->get_node_data();
  dyn::Node* node_dynamic = node_exporter->get_node_dynamic();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::ply::Node* node_player = node_data->get_node_player();

  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->dyn_player = node_player->get_dyn_player();
  this->io_struct = node_exporter->get_io_struct();
  this->dat_selection = node_graph->get_dat_selection();

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::draw_header(utl::base::Element* element){
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(element);
  //---------------------------

  this->item_update(sensor);

  this->display_action(sensor);
  this->display_path();
  this->display_format();

  //---------------------------
  ImGui::Separator();
}

//Header function
void Recorder::display_action(dyn::base::Sensor* sensor){
  //---------------------------

  if(!sensor->state.record){
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
    if(ImGui::Button("Record##444", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
      dyn_player->button_record();
      this->item_operation(sensor);
    }
    ImGui::PopStyleColor(2);
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(120, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(150, 50, 50, 255));
    if(ImGui::Button("Stop##444", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
      dyn_player->button_record();
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
void Recorder::item_update(dyn::base::Sensor* sensor){
  //---------------------------

  //Actualize current name
  if(sensor != nullptr && io_struct->path.name != sensor->name){
    utl::base::Data* data = &sensor->data;
    io_struct->path.name = sensor->name;

    this->vec_format.clear();
    for(int i=0; i<sensor->vec_recorder.size(); i++){
      this->vec_format.push_back(sensor->vec_recorder[i]->format);
    }
  }

  //---------------------------
}
void Recorder::item_operation(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  std::string format = (io_struct->path.format != "-") ? io_struct->path.format : "";

  utl::base::Data* data = &entity->data;
  data->name = io_struct->path.name;
  data->path.directory = io_struct->path.directory;
  data->path.name = data->name;
  data->path.format = format;

  //---------------------------
}

}
