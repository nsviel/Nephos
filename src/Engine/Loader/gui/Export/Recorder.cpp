#include "Recorder.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr::gui::exporter{

//Constructor / Destructor
Recorder::Recorder(ldr::Node* node_loader){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();
  dyn::Node* node_dynamic = node_loader->get_node_dynamic();

  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->dyn_player = node_dynamic->get_dyn_player();
  this->ldr_struct = node_loader->get_ldr_struct();

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::design_header(dyn::base::Sensor* sensor){
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
      this->item_operation();
    }
    ImGui::PopStyleColor(2);
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(120, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(150, 50, 50, 255));
    if(ImGui::Button("Stop##444", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
      dyn_player->button_record();
      this->item_operation();
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
  strncpy(str_n, ldr_struct->current_dir.c_str(), sizeof(str_n) - 1);
  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  if(ImGui::InputText("##exporter_dir", str_n, IM_ARRAYSIZE(str_n))){
    ldr_struct->current_dir = (string)str_n;
  }
  ImGui::PopStyleColor(2);
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
      ldr_struct->current_format = vec_format[i];
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
  if(sensor != nullptr && ldr_struct->current_name != sensor->name){
    utl::base::Data* data = &sensor->data;
    ldr_struct->current_name = sensor->name;

    this->vec_format.clear();
    for(int i=0; i<sensor->vec_recorder.size(); i++){
      this->vec_format.push_back(sensor->vec_recorder[i]->format);
    }
  }

  //---------------------------
}
void Recorder::item_operation(){
  //---------------------------

  dyn_struct->recorder.dir = ldr_struct->current_dir;
  dyn_struct->recorder.name = ldr_struct->current_name;
  dyn_struct->recorder.format = ldr_struct->current_format;
  dyn_struct->recorder.enable = !dyn_struct->recorder.enable;

  //---------------------------
}

}
