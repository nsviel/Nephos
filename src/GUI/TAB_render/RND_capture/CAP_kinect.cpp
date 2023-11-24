#include "CAP_kinect.h"
#include "CAP_capture.h"

#include <GUI.h>
#include <Utility.h>
#include <UTL_capture/UTL_capture.h>
#include <UTL_capture/UTL_kinect/Kinect.h>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_swarm.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_swarm.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_configuration.h>


//Constructor / Destructor
CAP_kinect::CAP_kinect(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Utility* utility = gui->get_utility();
  UTL_capture* utl_capture = utility->get_utl_capture();

  this->kinect = utl_capture->get_kinect();
  this->k4a_swarm = kinect->get_k4a_swarm();
  this->k4a_configuration = new K4A_configuration();

  this->item_width = 100;

  //---------------------------
}
CAP_kinect::~CAP_kinect(){}

//Main function
void CAP_kinect::design_panel(){
  //---------------------------

  if (ImGui::BeginTabBar("kinect_tab")){

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Capture##12323", NULL)){
      this->kinect_devices();
      this->configuration_device();
      this->configuration_general();
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

//Kinect device
void CAP_kinect::kinect_devices(){
  //---------------------------

  vector<K4A_device*>& vec_device = kinect->get_vec_device();

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;
  static int selected_device = -1;
  if(ImGui::BeginTable("database_view", 3, flags)){
    if(vec_device.size() == 0){
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::TableNextColumn();
      ImGui::Text("(No available devices)");
    }
    else{
      ImGui::TableSetupColumn("");
      ImGui::TableSetupColumn("ID");
      ImGui::TableSetupColumn("Serial number");
      ImGui::TableHeadersRow();
      for(int i=0; i<vec_device.size(); i++){
        K4A_device* device = vec_device[i];

        ImGui::TableNextRow();
        ImGui::TableNextColumn();

        ImGui::PushID(device->serial_number.c_str());
        ImGui::Text("Azur Kinect");
        ImGui::TableNextColumn();
        ImGui::Text("%d", device->index);
        ImGui::TableNextColumn();
        if (ImGui::Selectable(device->serial_number.c_str(), selected_device == i, ImGuiSelectableFlags_SpanAllColumns)){
          kinect->set_selected_device(device);
          selected_device = i;
        }
        ImGui::PopID();
      }
    }

    ImGui::EndTable();
  }

  if(ImGui::Button("Refresh", ImVec2(item_width, 0))){
    k4a_swarm->refresh_connected_device_list();
  }

  //---------------------------
}
void CAP_kinect::configuration_device(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  ImGui::Separator();
  string device_header = "Device S/N: " + device->serial_number;
  ImGui::Text("%s", device_header.c_str());
  ImGui::SameLine();{
    if(ImGui::Button("Close", ImVec2(item_width, 0))){
    }
  }

  this->firmware_info();
  ImGui::Separator();

  this->configuration_depth();
  this->configuration_color();

  //---------------------------
}
void CAP_kinect::configuration_depth(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  ImGui::Checkbox("Depth enabled", &device->depth.enabled);
  if(device->depth.enabled){
    ImGui::Indent();
    if(ImGui::TreeNode("Depth configuration")){
      static int depth_mode = 1;
      if(ImGui::RadioButton("NFOV Binned", &depth_mode, 0)){
        device->depth.mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("NFOV Unbinned", &depth_mode, 1)){
        device->depth.mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
      }
      if(ImGui::RadioButton("WFOV Binned", &depth_mode, 2)){
        device->depth.mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("WFOV Unbinned", &depth_mode, 3)){
        device->depth.mode = K4A_DEPTH_MODE_WFOV_UNBINNED;
      }
      if(ImGui::RadioButton("Passive IR", &depth_mode, 4)){
        device->depth.mode = K4A_DEPTH_MODE_PASSIVE_IR;
      }

      ImGui::TreePop();
    }
    ImGui::Unindent();
  }

  //---------------------------
}
void CAP_kinect::configuration_color(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  ImGui::Checkbox("Color enabled", &device->color.enabled);
  if(device->color.enabled){
    ImGui::Indent();
    if(ImGui::TreeNode("Color configuration")){

      //Format
      ImGui::Text("Format");
      static int color_format = 0;
      if(ImGui::RadioButton("BGRA", &color_format, 0)){
        device->color.format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("MJPG", &color_format, 1)){
        device->color.format = K4A_IMAGE_FORMAT_COLOR_MJPG;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("NV12", &color_format, 2)){
        device->color.format = K4A_IMAGE_FORMAT_COLOR_NV12;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("YUY2", &color_format, 3)){
        device->color.format = K4A_IMAGE_FORMAT_COLOR_YUY2;
      }

      //Resolution
      ImGui::Text("Resolution [16:9]");
      ImGui::Indent();
      static int color_resolution = 0;
      if(ImGui::RadioButton("720p", &color_resolution, 0)){
        device->color.resolution = K4A_COLOR_RESOLUTION_720P;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("1080p", &color_resolution, 1)){
        device->color.resolution = K4A_COLOR_RESOLUTION_1080P;
      }
      if(ImGui::RadioButton("1440p", &color_resolution, 2)){
        device->color.resolution = K4A_COLOR_RESOLUTION_1440P;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("2160p", &color_resolution, 3)){
        device->color.resolution = K4A_COLOR_RESOLUTION_2160P;
      }
      ImGui::Unindent();

      ImGui::Text("Resolution [4:3]");
      ImGui::Indent();
      if(ImGui::RadioButton("1536p", &color_resolution, 4)){
        device->color.resolution = K4A_COLOR_RESOLUTION_1536P;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("3072p", &color_resolution, 5)){
        device->color.resolution = K4A_COLOR_RESOLUTION_3072P;
      }
      ImGui::Unindent();

      ImGui::TreePop();
    }

    if(ImGui::TreeNode("Color control")){
      //Exposur time
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Exposure Time", &device->color.exposure.value, 488, 1000000, "%d us");

      //White Balance
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("White Balance", &device->color.white_balance.value, 2500, 12500, "%d K");

      //Brightness
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Brightness", &device->color.brightness.value, 0, 255, "%d");

      //Contrast
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Contrast", &device->color.contrast.value, 0, 10, "%d");

      //Saturation
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Saturation", &device->color.saturation.value, 0, 63, "%d");

      //Sharpness
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Sharpness", &device->color.sharpness.value, 0, 4, "%d");

      //Gain
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Gain", &device->color.gain.value, 0, 255, "%d");

      //Backlight Compensation
      ImGui::Checkbox("Backlight Compensation", &device->color.backlight_compensation.value);

      //Power frequency
      ImGui::Text("Power Frequency");
      static int power_frequency = 0;
      if(ImGui::RadioButton("50Hz", &power_frequency, 0)){
        device->color.power_frequency.value = "50Hz";
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("60Hz", &power_frequency, 1)){
        device->color.power_frequency.value = "60Hz";
      }

      //Refresh / reset buttons
      if (ImGui::Button("Refresh")){

      }
      ImGui::SameLine();
      if (ImGui::Button("Reset to default##RGB")){

      }

      ImGui::TreePop();
    }

    ImGui::Unindent();
  }

  //---------------------------
}
void CAP_kinect::configuration_general(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  ImGui::Text("Framerate");
  static int framerate = 0;
  if(ImGui::RadioButton("30 FPS", &framerate, 0)){
    device->config.fps = K4A_FRAMES_PER_SECOND_30;
  }
  ImGui::SameLine();
  if(ImGui::RadioButton("15 FPS", &framerate, 1)){
    device->config.fps = K4A_FRAMES_PER_SECOND_15;
  }
  ImGui::SameLine();
  if(ImGui::RadioButton("5 FPS", &framerate, 2)){
    device->config.fps = K4A_FRAMES_PER_SECOND_5;
  }

  ImGui::Checkbox("Disable streaming LED", &device->config.disable_streaming_indicator);

  if(ImGui::Button("Run capture", ImVec2(item_width, 0))){
    kinect->run_selected_device();
  }

  //---------------------------
}
void CAP_kinect::firmware_info(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if (ImGui::TreeNode("Device Firmware Version Info")){
    k4a_hardware_version_t versionInfo = device->config.version;
    ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
    if(ImGui::BeginTable("device##firmware", 2)){
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
    }

    ImGui::TreePop();
  }

  //---------------------------
}

void CAP_kinect::playback_stuff(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  //General info
  if(ImGui::BeginTable("playback_table##general", 2)){
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Path "); ImGui::TableNextColumn();
    ImGui::TextColored(ImVec4(0.4f,1.0f,0.4f,1.0f), "%s", device->info.file_path.c_str());

    ImGui::EndTable();
  }

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
void CAP_kinect::recorder_stuff(){
  K4A_device* device = kinect->get_selected_device();
  if(device == nullptr) return;
  //---------------------------

  if(ImGui::Button("Record")){
    //k4a_recorder->record_mkv(device);
  }

  //---------------------------
}
