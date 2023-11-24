#include "GUI_kinect.h"

#include <GUI.h>
#include <Utility.h>
#include <UTL_capture/UTL_capture.h>
#include <UTL_capture/UTL_kinect/Kinect.h>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_swarm.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_swarm.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_configuration.h>
#include <RND_kinect/KIN_configuration.h>
#include <RND_kinect/KIN_capture.h>


//Constructor / Destructor
GUI_kinect::GUI_kinect(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Utility* utility = gui->get_utility();
  UTL_capture* utl_capture = utility->get_utl_capture();

  this->kinect = utl_capture->get_kinect();
  this->k4a_swarm = kinect->get_k4a_swarm();
  this->kin_configuration = new KIN_configuration(kinect);

  this->item_width = 100;

  //---------------------------
}
GUI_kinect::~GUI_kinect(){}

//Main function
void GUI_kinect::design_panel(){
  //---------------------------

  if (ImGui::BeginTabBar("kinect_tab")){

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Capture##12323", NULL)){
      kin_configuration->kinect_configuration();
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Playback##4567", NULL)){
      this->playback_stuff();
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Recorder##4567", NULL)){
      this->recorder_stuff();
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}


void GUI_kinect::playback_stuff(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  //General info
  if(ImGui::BeginTable("playback_table##general", 2)){
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Path"); ImGui::TableNextColumn();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", device->info.file_path.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Duration"); ImGui::TableNextColumn();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%.2f s", (float)device->info.file_duration/1000000);

    ImGui::EndTable();
  }
  ImGui::Separator();

  //Data info
  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Recording settings");
  if(ImGui::BeginTable("playback_table##data", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("FPS"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", device->info.info_fps.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth mode"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", device->info.info_depth_mode.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color format"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", device->info.info_color_format.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color resolution"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", device->info.info_color_resolution.c_str());

    ImGui::EndTable();
  }
  ImGui::Separator();

  //Stream info
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Stream info");
  if(ImGui::BeginTable("playback_table##stream", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", device->info.is_color ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", device->info.is_depth ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("IR enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", device->info.is_infrared ? "Yes" : "No");

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("IMU enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", device->info.is_imu ? "Yes" : "No");

    ImGui::EndTable();
  }
  ImGui::Separator();

  //Synchro info
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Sync settings");
  if(ImGui::BeginTable("playback_table##synchro", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth/color delay (us)"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", device->info.depth_delay_off_color_us);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Sync mode"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", device->info.info_wired_sync_mode.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Start timestamp offset"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%d", device->info.start_timestamp_offset_us);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("IMU enabled"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%lu", device->info.file_duration);

    ImGui::EndTable();
  }
  ImGui::Separator();

  //Device info
  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Device info");
  if(ImGui::BeginTable("playback_table##device", 2)){
    ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Device S/N"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", device->info.info_device_serial_number.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("RGB camera FW"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", device->info.info_color_firmware_version.c_str());

    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Depth camera FW"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%s", device->info.info_depth_firmware_version.c_str());

    ImGui::EndTable();
  }
  ImGui::Separator();

  //---------------------------
}
void GUI_kinect::recorder_stuff(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if(ImGui::Button("Record")){
    //k4a_recorder->record_mkv(device);
  }

  //---------------------------
}
