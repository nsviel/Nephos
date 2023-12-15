#include "Playback.h"

#include <image/IconsFontAwesome5.h>
#include <Engine/Capture/Kinect/Thread/K4A_playback.h>
#include <Engine/Capture/Kinect/Device/K4A_swarm.h>


namespace gui::kinect{

//Constructor / Destructor
Playback::Playback(eng::kinect::Kinect* kinect){
  //---------------------------

  this->kinect = kinect;
  this->k4a_swarm = kinect->get_k4a_swarm();

  //---------------------------
}
Playback::~Playback(){}

//Main function
void Playback::kinect_playback(){
  K4A_device* device = k4a_swarm->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if(!device->device.is_virtual) ImGui::BeginDisabled();
  this->show_file();
  this->show_recording();
  this->show_stream();
  this->show_synchro();
  this->show_device();
  if(!device->device.is_virtual) ImGui::EndDisabled();

  //---------------------------
}

//Design function
void Playback::show_file(){
  K4A_device* device = k4a_swarm->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  //General info
  if(ImGui::BeginTable("playback_table##general", 2)){
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Path"); ImGui::TableNextColumn();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", device->file.path.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Duration"); ImGui::TableNextColumn();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%.2f s", (float)device->file.duration);

    ImGui::EndTable();
  }
  ImGui::Separator();

  //---------------------------
}
void Playback::show_recording(){
  K4A_device* device = k4a_swarm->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if(ImGui::TreeNode("Recording setting")){

    ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
    if(ImGui::BeginTable("playback_table##data", 2)){
      ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Frame rate"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", device->file.fps.c_str());

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Depth mode"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", device->file.depth_mode.c_str());

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Color format"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", device->file.color_format.c_str());

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Color resolution"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", device->file.color_resolution.c_str());

      ImGui::EndTable();
    }

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}
void Playback::show_stream(){
  K4A_device* device = k4a_swarm->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if(ImGui::TreeNode("Stream info")){

    ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
    if(ImGui::BeginTable("playback_table##stream", 2)){
      ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Color enabled"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", device->file.is_color ? "Yes" : "No");

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Depth enabled"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", device->file.is_depth ? "Yes" : "No");

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("IR enabled"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", device->file.is_infrared ? "Yes" : "No");

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("IMU enabled"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", device->file.is_imu ? "Yes" : "No");

      ImGui::EndTable();
    }

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}
void Playback::show_synchro(){
  K4A_device* device = k4a_swarm->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if(ImGui::TreeNode("Sync settings")){

    ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
    if(ImGui::BeginTable("playback_table##synchro", 2)){
      ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Depth/color delay (us)"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%d", device->synchro.depth_delay_off_color_us);

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Sync mode"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", device->file.wired_sync_mode.c_str());

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Start timestamp offset"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%d", device->synchro.start_timestamp_offset_us);

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Recording length"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f", device->file.duration);

      ImGui::EndTable();
    }

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}
void Playback::show_device(){
  K4A_device* device = k4a_swarm->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if(ImGui::TreeNode("Device info")){

    ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
    if(ImGui::BeginTable("playback_table##device", 2)){
      ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Device S/N"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", device->file.device_serial_number.c_str());

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("RGB camera FW"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", device->file.color_firmware_version.c_str());

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Depth camera FW"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%s", device->file.depth_firmware_version.c_str());

      ImGui::EndTable();
    }

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}

}
