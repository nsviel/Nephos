#include "Playback.h"

#include <Engine/Capture/K4N/Thread/K4A_playback.h>
#include <Engine/Capture/K4N/Device/Swarm.h>


namespace gui::kinect{

//Constructor / Destructor
Playback::Playback(k4n::Node* node_kinect){
  //---------------------------

  this->node_kinect = node_kinect;
  this->k4a_swarm = node_kinect->get_k4a_swarm();

  //---------------------------
}
Playback::~Playback(){}

//Main function
void Playback::kinect_playback(){
  k4n::Device* k4n_device = k4a_swarm->get_selected_device();
  if(k4n_device == nullptr || !k4n_device->device.is_playback) return;
  //---------------------------

  ImGui::Separator();
  if(ImGui::TreeNode("Configuration")){
    this->show_info_device();
    this->show_info_color();
    this->show_info_depth();
    this->show_info_synch();

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}

//Design function
void Playback::show_info_device(){
  k4n::Device* k4n_device = k4a_swarm->get_selected_device();
  if(k4n_device == nullptr) return;
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Device");
  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  if(ImGui::BeginTable("playback_table##k4n_device", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Device S/N"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4n_device->device.serial_number.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("IMU enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4n_device->imu.config.enabled ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Frame rate"); ImGui::TableNextColumn();
    string fps_str = to_string(k4n_device->device.fps) + " fps";
    ImGui::TextColored(color, "%s", fps_str.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
void Playback::show_info_color(){
  k4n::Device* k4n_device = k4a_swarm->get_selected_device();
  if(k4n_device == nullptr) return;
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Color");
  if(ImGui::BeginTable("playback_table##data", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4n_device->color.config.enabled ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color format"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4n_device->color.config.format_str.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color resolution"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4n_device->color.config.resolution_str.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color firmware"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4n_device->color.config.firmware_version.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
void Playback::show_info_depth(){
  k4n::Device* k4n_device = k4a_swarm->get_selected_device();
  if(k4n_device == nullptr) return;
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Depth");
  if(ImGui::BeginTable("playback_table##stream", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4n_device->depth.config.enabled ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("IR enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4n_device->ir.config.enabled ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth mode"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4n_device->depth.config.mode_str.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth camera FW"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4n_device->depth.config.firmware_version.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
void Playback::show_info_synch(){
  k4n::Device* k4n_device = k4a_swarm->get_selected_device();
  if(k4n_device == nullptr) return;
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Synchronization");
  if(ImGui::BeginTable("playback_table##synchro", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth/color delay (us)"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", k4n_device->synchro.depth_delay_off_color_us);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Sync mode"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4n_device->synchro.wired_sync_mode_str.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Start timestamp offset"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", k4n_device->synchro.start_timestamp_offset_us);

    ImGui::EndTable();
  }

  //---------------------------
}


}
