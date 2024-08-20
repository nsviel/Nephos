#include "Info.h"

#include <Data/Player/Namespace.h>
#include <Data/Base/Namespace.h>
#include <imgui/core/imgui.h>


namespace dat::ply::gui{

//Constructor / Destructor
Info::Info(){
  //---------------------------



  //---------------------------
}
Info::~Info(){}

//Main function
void Info::design_info(utl::base::Element* element){
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Info##dynamic")){
    this->path_info(element);
    this->sensor_info(element);
    //this->playback_info(element);
  }

  //---------------------------
}

//Subfunction
void Info::path_info(utl::base::Element* element){
  dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element);
  if(entity == nullptr) return;
  //---------------------------

  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  utl::base::Data* data = &entity->data;
  utl::base::Pose* pose = &entity->pose;

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Path");
  ImGui::BeginTable("sensor##info", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 75.0f);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);

  //Data
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Data"); ImGui::TableNextColumn();
  std::string path_data = data->path.directory + data->path.name + data->path.format;
  if(path_data == "") path_data = "(not defined)";
  ImGui::TextColored(color, "%s", path_data.c_str());

  //Transformation
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Transform"); ImGui::TableNextColumn();
  std::string path_transfo = pose->path.directory + pose->path.name + pose->path.format;
  if(path_transfo == "") path_transfo = "(not defined)";
  ImGui::TextColored(color, "%s", path_transfo.c_str());

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Info::sensor_info(utl::base::Element* element){
/*  dyn::prc::base::Sensor* sensor = dynamic_cast<dyn::prc::base::Sensor*>(element);
  if(sensor == nullptr) return;
  //---------------------------

  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Sensor");
  ImGui::BeginTable("sensor##info", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 75.0f);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);

  //Timestamp
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Timestamp"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%.2fs - %.2fs [%.2fs]", sensor->timestamp.begin, sensor->timestamp.end, sensor->timestamp.duration);

  //Recording time
  if(sensor->state.record){
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Record"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", sensor->timestamp.record);
  }

  /*
  //Recording file size
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Size"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%.2f Mo", master->recorder.file_size);

  //FPS
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("FPS"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d fps", player->fps_cur);
  ImGui::SetNextItemWidth(50); ImGui::TableNextColumn();
  ImGui::SliderInt("##56765", &player->fps_qry, 1, 120);

  //Size
  if(player->size != 0){
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Size"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f Mo", player->size);
  }
*/
  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Info::playback_info(utl::base::Element* element){
  if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)) return;
  //---------------------------

  /*
  dat::base::Set* set = dynamic_cast<dat::base::Set*>(element);
  dyn::prc::base::Player* player = &set->player;
  if(player == nullptr) return;

  if(ImGui::CollapsingHeader("Info##dynamic")){

    ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
    ImGui::BeginTable("master##playback_info", 3);
    //Duration
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Duration"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", player->ts_duration);

    //FPS
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("FPS"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d fps", player->fps_cur);
    ImGui::SetNextItemWidth(50); ImGui::TableNextColumn();
    ImGui::SliderInt("##56765", &player->fps_qry, 1, 120);

    //Path data
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Path"); ImGui::TableNextColumn();
    std::string path = (player->path.build() != "") ? player->path.build() : "(not defined)";
    ImGui::TextColored(color, "%s", path.c_str());

    //Size
    if(player->size != 0){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Size"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f Mo", player->size);
    }

    ImGui::EndTable();

    //Recording time
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Record"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", master->recorder.ts_rec);

    //Recording file size
    if(master->recorder.mode == dyn::prc::recorder::MKV){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Size"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f Mo", master->recorder.file_size);
    }
  }

  }
*/

  //---------------------------
}

}
