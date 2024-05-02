#include "Playback.h"

#include <Kinect/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Playback::Playback(k4n::Node* node_k4n){
  //---------------------------

  this->node_k4n = node_k4n;
  this->k4n_swarm = node_k4n->get_k4n_swarm();

  //---------------------------
}
Playback::~Playback(){}

//Main function
void Playback::show_master_playback(k4n::dev::Master* master){
  if(master == nullptr) return;
  if(master->mode == k4n::dev::CAPTURE) return;
  //---------------------------

  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  if(ImGui::BeginTable("master##playback_info", 2)){
    //Duration
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Duration"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", master->player->duration);

    //FPS
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("FPS"); ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(125);
    ImGui::SliderInt("##56765", &master->operation.fps, 1, 120);

    ImGui::EndTable();
  }

  //---------------------------
}
void Playback::show_sensor_configuration(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  if(sensor->master->mode == k4n::dev::CAPTURE) return;
  //---------------------------

  this->show_info_device(sensor);
  this->show_info_color(sensor);
  this->show_info_depth(sensor);
  this->show_info_synch(sensor);

  //---------------------------
  ImGui::Separator();
}

//Design function
void Playback::show_info_device(k4n::dev::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Device");
  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  if(ImGui::BeginTable("playback_table##sensor", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Device S/N"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->param.serial_number.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("IMU enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->imu.config.enabled ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Frame rate"); ImGui::TableNextColumn();
    string fps_str = sensor->param.fps_mode + " fps";
    ImGui::TextColored(color, "%s", fps_str.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
void Playback::show_info_color(k4n::dev::Sensor* sensor){
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Color");
  if(ImGui::BeginTable("playback_table##data", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->color.config.enabled ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color format"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->color.config.format_str.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color resolution"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->color.config.resolution_str.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color firmware"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->color.config.firmware_version.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
void Playback::show_info_depth(k4n::dev::Sensor* sensor){
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Depth");
  if(ImGui::BeginTable("playback_table##stream", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->depth.config.enabled ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("IR enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->ir.config.enabled ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth mode"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->depth.config.mode_str.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth camera FW"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->depth.config.firmware_version.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
void Playback::show_info_synch(k4n::dev::Sensor* sensor){
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Synchronization");
  if(ImGui::BeginTable("playback_table##synchro", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth/color delay (us)"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", sensor->playback.depth_delay_off_color_us);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Sync mode"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", sensor->playback.wired_sync_mode_str.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Start timestamp offset"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", sensor->playback.start_timestamp_offset_us);

    ImGui::EndTable();
  }

  //---------------------------
}


}
