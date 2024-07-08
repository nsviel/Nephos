#include "Playback.h"

#include <Kinect/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Playback::Playback(k4n::Node* node_k4n){
  //---------------------------

  this->node_k4n = node_k4n;
  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Playback::~Playback(){}

//Main function
void Playback::show_parameter(k4n::base::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  this->show_transformation_mode(sensor->set_parent);

  if(k4n::playback::Sensor* playback = dynamic_cast<k4n::playback::Sensor*>(sensor)){
    this->show_info_device(playback);
    this->show_info_color(playback);
    this->show_info_depth(playback);
    this->show_info_synch(playback);
  }

  //---------------------------
  ImGui::Separator();
}

//Design function
void Playback::show_transformation_mode(dat::base::Set* set){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Transformation");

  ImGui::RadioButton("Depth to color", &k4n_struct->config.depth.transformation_mode, k4n::depth::DEPTH_TO_COLOR);
  ImGui::SameLine();
  ImGui::RadioButton("Color to depth", &k4n_struct->config.depth.transformation_mode, k4n::depth::COLOR_TO_DEPTH);

  //---------------------------
  ImGui::Separator();
}
void Playback::show_firmware_info(k4n::base::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Device Firmware Version Info");

  k4a_hardware_version_t versionInfo = sensor->device.version;
  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::BeginTable("device##firmware", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("RGB camera"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%u.%u.%u", versionInfo.rgb.major, versionInfo.rgb.minor, versionInfo.rgb.iteration);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Depth camera"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%u.%u.%u", versionInfo.depth.major, versionInfo.depth.minor, versionInfo.depth.iteration);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Audio"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%u.%u.%u", versionInfo.audio.major, versionInfo.audio.minor, versionInfo.audio.iteration);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Build config"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", versionInfo.firmware_build == K4A_FIRMWARE_BUILD_RELEASE ? "Release" : "Debug");

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Signature type"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", versionInfo.firmware_signature == K4A_FIRMWARE_SIGNATURE_MSFT ? "Microsoft" : versionInfo.firmware_signature == K4A_FIRMWARE_SIGNATURE_TEST ? "Test" : "Unsigned");

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Playback::show_info_device(k4n::playback::Sensor* sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Device");
  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::BeginTable("playback_table##sensor", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Device S/N"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor->serial_number.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("IMU enabled"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor->imu.config.enabled ? "Yes" : "No");

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Frame rate"); ImGui::TableNextColumn();
  //string fps_str = sensor->set_parent->fps.mode_str + " fps";
  //ImGui::TextColored(color, "%s", fps_str.c_str());

  ImGui::EndTable();

  //---------------------------
}
void Playback::show_info_color(k4n::playback::Sensor* sensor){
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Color");
  ImGui::BeginTable("playback_table##data", 2);
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

  //---------------------------
}
void Playback::show_info_depth(k4n::playback::Sensor* sensor){
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Depth");
  ImGui::BeginTable("playback_table##stream", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Depth enabled"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor->depth.config.enabled ? "Yes" : "No");

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Depth resolution"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor->depth.config.resolution.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Depth mode"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor->depth.config.mode_str.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Depth camera FW"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor->depth.config.firmware_version.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("IR enabled"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor->ir.config.enabled ? "Yes" : "No");

  ImGui::EndTable();

  //---------------------------
}
void Playback::show_info_synch(k4n::playback::Sensor* sensor){
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Synchronization");
  ImGui::BeginTable("playback_table##synchro", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Depth/color delay (us)"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d", k4n_struct->config.synchro.depth_delay_off_color_us);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Sync mode"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", k4n_struct->config.synchro.wired_mode_str.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Start timestamp offset"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d", k4n_struct->config.synchro.start_timestamp_offset_us);

  ImGui::EndTable();

  //---------------------------
}



}
