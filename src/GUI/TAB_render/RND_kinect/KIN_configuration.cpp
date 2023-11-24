#include "KIN_configuration.h"

#include <GUI.h>
#include <UTL_capture/UTL_kinect/Kinect.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_swarm.h>


//Constructor / Destructor
KIN_configuration::KIN_configuration(Kinect* kinect){
  //---------------------------

  this->kinect = kinect;
  this->k4a_swarm = kinect->get_k4a_swarm();

  this->item_width = 100;

  //---------------------------
}
KIN_configuration::~KIN_configuration(){}

//Main function
void KIN_configuration::kinect_configuration(){
  //---------------------------

  this->kinect_devices();
  this->configuration_device();
  this->configuration_general();

  //---------------------------
}

//Subfunction
void KIN_configuration::kinect_devices(){
  vector<K4A_device*>& vec_device = kinect->get_vec_device();
  //---------------------------

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;
  static int selected_device = -1;
  if(ImGui::BeginTable("database_view", 3, flags)){
    if(kinect->get_nb_device_real() == 0){
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
        if(device->is_virtual) continue;

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
void KIN_configuration::configuration_device(){
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
void KIN_configuration::configuration_depth(){
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
void KIN_configuration::configuration_color(){
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
void KIN_configuration::configuration_general(){
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
void KIN_configuration::firmware_info(){
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
