#include "Info.h"

#include <Dynamic/Namespace.h>


namespace dyn::gui{

//Constructor / Destructor
Info::Info(dyn::Node* node_dynamic){
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

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Path");
  ImGui::BeginTable("sensor##info", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 75.0f);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);

  //Data
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Data"); ImGui::TableNextColumn();
  string path_data = (data->path.data != "") ? data->path.directory + data->path.data : "(not defined)";
  ImGui::TextColored(color, "%s", path_data.c_str());

  //Transformation
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Transform"); ImGui::TableNextColumn();
  string path_transfo = (data->path.transformation != "") ? data->path.directory + data->path.transformation : "(not defined)";
  ImGui::TextColored(color, "%s", path_transfo.c_str());

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Info::sensor_info(utl::base::Element* element){
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(element);
  if(sensor == nullptr) return;
  //---------------------------

  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Sensor");
  ImGui::BeginTable("sensor##info", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 75.0f);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);

  //Duration
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Duration"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%.2f s", sensor->timestamp.duration);

  //Recording time
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Record"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%.2f s", sensor->timestamp.record);

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
  dyn::base::Player* player = &set->player;
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
    string path = (player->path.data != "") ? player->path.data : "(not defined)";
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
    if(master->recorder.mode == dyn::recorder::MKV){
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
