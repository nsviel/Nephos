#include "Playback.h"

#include <image/IconsFontAwesome5.h>
#include <Utility/Capture/Kinect/Thread/K4A_replay.h>


namespace gui::kinect{

//Constructor / Destructor
Playback::Playback(util::kinect::Kinect* kinect){
  //---------------------------

  this->kinect = kinect;

  //---------------------------
}
Playback::~Playback(){}

//Main function
void Playback::kinect_playback(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if(!device->device.is_virtual) ImGui::BeginDisabled();
  this->show_player();
  this->show_file();
  this->show_recording();
  this->show_stream();
  this->show_synchro();
  this->show_device();
  if(!device->device.is_virtual) ImGui::EndDisabled();

  //---------------------------
}

//Subfunction
void Playback::show_player(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  bool is_playing = true;

  //Slider
  ImVec2 image_size = ImGui::GetContentRegionAvail();
  ImGui::SetNextItemWidth(image_size.x);
  if(ImGui::SliderFloat("###Slider_playback", &device->color.image.timestamp, device->file.ts_beg, device->file.ts_end, "%.2f s")){
    device->k4a_replay->set_current_timestamp(device->color.image.timestamp);
  }

  //Slider buttons
  bool* thread_play = device->k4a_replay->get_thread_play();
  bool* thread_paused = device->k4a_replay->get_thread_pause();
  bool* thread_restart = device->k4a_replay->get_thread_restart();

  ImU32 color = (*thread_paused || !*thread_play) ? IM_COL32(46, 133, 45, 255) : IM_COL32(133, 133, 0, 255);
  string icon = (*thread_paused || !*thread_play) ? (ICON_FA_PLAY "##36") : (ICON_FA_PAUSE "##36");
  ImGui::PushStyleColor(ImGuiCol_Button, color);
  if(ImGui::Button(icon.c_str())){
    if(!*thread_play){
      device->k4a_replay->set_current_timestamp(device->file.ts_beg);
      *thread_play = true;
      *thread_paused = false;
    }else{
      *thread_paused = !*thread_paused;
    }
  }
  ImGui::PopStyleColor(1);

  ImGui::SameLine();
  if(!*thread_paused) ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
  if (ImGui::Button(ICON_FA_STOP "##37")){
    device->k4a_replay->set_current_timestamp(device->file.ts_end);
    *thread_restart = false;
    *thread_play = false;
    *thread_paused = false;
  }
  if(!*thread_paused) ImGui::PopStyleColor(1);
  ImGui::SameLine();
  if(*thread_restart) ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 133, 133, 255));
  if (ImGui::Button(ICON_FA_REPEAT "##37")){
    *thread_restart = !*thread_restart;
  }
  if(*thread_restart) ImGui::PopStyleColor(1);

  //---------------------------
}
void Playback::show_file(){
  K4A_device* device = kinect->get_selected_device();
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
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if(ImGui::TreeNode("Recording setting")){

    ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
    if(ImGui::BeginTable("playback_table##data", 2)){
      ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("FPS"); ImGui::TableNextColumn();
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
  K4A_device* device = kinect->get_selected_device();
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
  K4A_device* device = kinect->get_selected_device();
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
      ImGui::Text("IMU enabled"); ImGui::TableNextColumn();
      ImGui::TextColored(color, "%.2f", device->file.duration);

      ImGui::EndTable();
    }

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}
void Playback::show_device(){
  K4A_device* device = kinect->get_selected_device();
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
