#include "Playback.h"

#include <Engine/Capture/K4N/Thread/K4A_playback.h>
#include <Engine/Capture/K4N/Device/K4A_swarm.h>


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
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr || !k4a_device->device.is_playback) return;
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
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Device");
  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  if(ImGui::BeginTable("playback_table##k4a_device", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Device S/N"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.device_serial_number.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("IMU enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.is_imu ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Frame rate"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.fps.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
void Playback::show_info_color(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Color");
  if(ImGui::BeginTable("playback_table##data", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.is_color ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color format"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.color_format.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color resolution"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.color_resolution.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color firmware"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.color_firmware_version.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
void Playback::show_info_depth(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Depth");
  if(ImGui::BeginTable("playback_table##stream", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.is_depth ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("IR enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.is_infrared ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth mode"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.depth_mode.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth camera FW"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.depth_firmware_version.c_str());

    ImGui::EndTable();
  }

  //---------------------------
}
void Playback::show_info_synch(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Synchronization");
  if(ImGui::BeginTable("playback_table##synchro", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth/color delay (us)"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", k4a_device->synchro.depth_delay_off_color_us);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Sync mode"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", k4a_device->playback.wired_sync_mode.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Start timestamp offset"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", k4a_device->synchro.start_timestamp_offset_us);

    ImGui::EndTable();
  }

  //---------------------------
}


}
