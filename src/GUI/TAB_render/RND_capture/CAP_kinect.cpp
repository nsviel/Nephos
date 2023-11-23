#include "CAP_kinect.h"
#include "CAP_capture.h"

#include <GUI.h>
#include <Utility.h>
#include <UTL_capture/UTL_capture.h>
#include <UTL_capture/UTL_kinect/Kinect.h>
#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>
#include <UTL_capture/UTL_kinect/K4A_recording/K4A_playback.h>


//Constructor / Destructor
CAP_kinect::CAP_kinect(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Utility* utility = gui->get_utility();
  UTL_capture* utl_capture = utility->get_utl_capture();

  this->kinect = utl_capture->get_kinect();
  this->struct_kinect = kinect->get_struct_kinect();
  this->k4a_device = new K4A_device(struct_kinect);
  this->k4a_playback = new K4A_playback(struct_kinect);

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

    ImGui::EndTabBar();
  }

  //---------------------------
}

//Kinect device
void CAP_kinect::kinect_devices(){
  //---------------------------

  vector<Struct_k4a_device>& vec_device = struct_kinect->vec_device;

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
      struct_kinect->selected_device = nullptr;
    }
    else{
      ImGui::TableSetupColumn("");
      ImGui::TableSetupColumn("ID");
      ImGui::TableSetupColumn("Serial number");
      ImGui::TableHeadersRow();
      for(int i=0; i<vec_device.size(); i++){
        Struct_k4a_device& device = vec_device[i];

        ImGui::TableNextRow();
        ImGui::TableNextColumn();

        ImGui::PushID(device.serial_number.c_str());
        ImGui::Text("Azur Kinect");
        ImGui::TableNextColumn();
        ImGui::Text("%d", device.index);
        ImGui::TableNextColumn();
        if (ImGui::Selectable(device.serial_number.c_str(), selected_device == i, ImGuiSelectableFlags_SpanAllColumns)){
          struct_kinect->selected_device = &struct_kinect->vec_device[i];
          selected_device = i;
        }
        ImGui::PopID();
      }
    }

    ImGui::EndTable();
  }

  if(ImGui::Button("Refresh", ImVec2(item_width, 0))){
    k4a_device->refresh_device_list();
  }

  //---------------------------
}
void CAP_kinect::configuration_device(){
  Struct_k4a_device* device = struct_kinect->selected_device;
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
  Struct_k4a_device* device = struct_kinect->selected_device;
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
  Struct_k4a_device* device = struct_kinect->selected_device;
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
  Struct_k4a_device* device = struct_kinect->selected_device;
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
    kinect->run();
  }
  //---------------------------
}
void CAP_kinect::firmware_info(){
  Struct_k4a_device* device = struct_kinect->selected_device;
  if(device == nullptr) return;
  //---------------------------

  if (ImGui::TreeNode("Device Firmware Version Info")){
    k4a_hardware_version_t versionInfo = device->config.version;
    ImGui::Text("RGB camera: %u.%u.%u", versionInfo.rgb.major, versionInfo.rgb.minor, versionInfo.rgb.iteration);
    ImGui::Text("Depth camera: %u.%u.%u", versionInfo.depth.major, versionInfo.depth.minor, versionInfo.depth.iteration);
    ImGui::Text("Audio: %u.%u.%u", versionInfo.audio.major, versionInfo.audio.minor, versionInfo.audio.iteration);

    ImGui::Text("Build Config: %s", versionInfo.firmware_build == K4A_FIRMWARE_BUILD_RELEASE ? "Release" : "Debug");
    ImGui::Text("Signature type: %s", versionInfo.firmware_signature == K4A_FIRMWARE_SIGNATURE_MSFT ? "Microsoft" : versionInfo.firmware_signature == K4A_FIRMWARE_SIGNATURE_TEST ? "Test" : "Unsigned");

    ImGui::TreePop();
  }

  //---------------------------
}

void CAP_kinect::playback_stuff(){
  //---------------------------

  k4a_playback->record_control("/home/aether/Desktop/francasque_0.mkv");

  Struct_k4a_info& struct_playback = k4a_playback->get_struct_record();


  ImGui::Text("Recording Settings");
  ImGui::Text("FPS:              %s", struct_playback.info_fps.c_str());
  ImGui::Text("Depth mode:       %s", struct_playback.info_depth_mode.c_str());
  ImGui::Text("Color format:     %s", struct_playback.info_color_format.c_str());
  ImGui::Text("Color resolution: %s", struct_playback.info_color_resolution.c_str());
  ImGui::Text("IMU enabled:      %s", struct_playback.is_imu ? "Yes" : "No");
  ImGui::Separator();

  ImGui::Text("Sync settings");
  ImGui::Text("Depth/color delay (us): %d", struct_playback.depth_delay_off_color_us);
  ImGui::Text("Sync mode:              %s", struct_playback.info_wired_sync_mode.c_str());
  ImGui::Text("Subordinate delay (us): %d", struct_playback.subordinate_delay_off_master_us);
  ImGui::Text("Start timestamp offset: %d", struct_playback.start_timestamp_offset_us);
  ImGui::Text("Recording Length (us):  %lu", struct_playback.info_recording_lenght_us);
  ImGui::Separator();

  ImGui::Text("Device info");
  ImGui::Text("Device S/N:      %s", struct_playback.info_device_serial_number.c_str());
  ImGui::Text("RGB camera FW:   %s", struct_playback.info_color_firmware_version.c_str());
  ImGui::Text("Depth camera FW: %s", struct_playback.info_depth_firmware_version.c_str());
  ImGui::Separator();

  //---------------------------
}
