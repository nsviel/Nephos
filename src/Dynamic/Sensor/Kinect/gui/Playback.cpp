#include "Playback.h"

#include <Kinect/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Playback::Playback(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_struct = node_k4n->get_k4n_structure();

  //---------------------------
}
Playback::~Playback(){}

//Main function
void Playback::show_info(k4n::playback::Sensor& sensor){
  //---------------------------

  //Table
  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Sensor");
  ImGui::BeginTable("sensor##info", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 75.0f);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);

  //Timestamp
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Timestamp"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%.2fs - %.2fs [%.2fs]", sensor.timestamp.begin, sensor.timestamp.end, sensor.timestamp.duration);

  //FPS
  int* fps = sensor.get_fps();
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("FPS"); ImGui::TableNextColumn();
  ImGui::SetNextItemWidth(50);
  ImGui::SliderInt("##56765", fps, 1, 120);

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Playback::show_parameter(k4n::playback::Sensor& sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Transformation");
  this->show_transformation_mode();

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Parametre");
  this->show_info_device(sensor);
  this->show_info_color(sensor);
  this->show_info_depth(sensor);
  this->show_info_synch(sensor);

  //---------------------------
  ImGui::Separator();
}

//Design function
void Playback::show_transformation_mode(){
  //---------------------------

  ImGui::RadioButton("Depth to color", &k4n_struct->transformation.mode, k4n::transformation::DEPTH_TO_COLOR);
  ImGui::SameLine();
  ImGui::RadioButton("Color to depth", &k4n_struct->transformation.mode, k4n::transformation::COLOR_TO_DEPTH);

  //---------------------------
  ImGui::Separator();
}
void Playback::show_firmware_info(k4n::playback::Sensor& sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Device Firmware Version Info");

  k4a_hardware_version_t versionInfo = sensor.device.firmware.version;
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
void Playback::show_info_device(k4n::playback::Sensor& sensor){
  //---------------------------

  ImGui::SeparatorText("Device");
  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::BeginTable("playback_table##sensor", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Device S/N"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.info.serial_number.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("IMU enabled"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.imu.config.enabled ? "Yes" : "No");

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Frame rate"); ImGui::TableNextColumn();
  //string fps_str = sensor.set_parent->fps.mode_str + " fps";
  //ImGui::TextColored(color, "%s", fps_str.c_str());

  ImGui::EndTable();

  //---------------------------
}
void Playback::show_info_color(k4n::playback::Sensor& sensor){
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::SeparatorText("Color");
  ImGui::BeginTable("playback_table##data", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Color enabled"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.color.config.enabled ? "Yes" : "No");

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Color format"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.config.color.format_str.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Color resolution"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.config.color.resolution_str.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Color firmware"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.device.firmware.color.c_str());

  ImGui::EndTable();

  //---------------------------
}
void Playback::show_info_depth(k4n::playback::Sensor& sensor){
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::SeparatorText("Depth");
  ImGui::BeginTable("playback_table##stream", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Depth enabled"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.depth.config.enabled ? "Yes" : "No");

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Depth resolution"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.config.depth.resolution_str.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Depth mode"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.config.depth.mode_str.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Depth camera FW"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.device.firmware.depth.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("IR enabled"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.infra.config.enabled ? "Yes" : "No");

  ImGui::EndTable();

  //---------------------------
}
void Playback::show_info_synch(k4n::playback::Sensor& sensor){
  //---------------------------

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::SeparatorText("Synchronization");
  ImGui::BeginTable("playback_table##synchro", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Depth/color delay (us)"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d", sensor.config.synchro.depth_delay_off_color_us);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Sync mode"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.config.synchro.wired_mode_str.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Start timestamp offset"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%d", sensor.config.synchro.start_timestamp_offset_us);

  ImGui::EndTable();

  //---------------------------
}



}
