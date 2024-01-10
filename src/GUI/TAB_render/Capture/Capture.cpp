#include "Capture.h"

#include <GUI.h>
#include <Engine/Capture/K4A/Device/K4A_swarm.h>


namespace gui::kinect{

//Constructor / Destructor
Capture::Capture(eng::kinect::Node* node_kinect){
  //---------------------------

  this->node_kinect = node_kinect;
  this->k4a_swarm = node_kinect->get_k4a_swarm();

  this->item_width = 100;

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::kinect_configuration(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr || k4a_device->device.is_playback) return;
  //---configuration_device----

  this->kinect_devices();
  ImGui::Separator();
  if(ImGui::TreeNode("Configuration")){
    this->configuration_depth();
    this->configuration_color();
    this->configuration_device();
    this->firmware_info();

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}

//Subfunction
void Capture::kinect_devices(){
  list<K4A_device*>& list_device = k4a_swarm->get_list_device();
  //---------------------------

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;
  static int selected_device = -1;
  if(ImGui::BeginTable("database_view", 3, flags)){
    if(k4a_swarm->get_nb_device() == 0){
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
      for(int i=0; i<list_device.size(); i++){
        K4A_device* k4a_device = *std::next(list_device.begin(), i);
        if(k4a_device->device.is_playback) continue;

        ImGui::TableNextRow();
        ImGui::TableNextColumn();

        ImGui::PushID(k4a_device->device.serial_number.c_str());
        ImGui::Text("Azur Kinect");
        ImGui::TableNextColumn();
        ImGui::Text("%d", k4a_device->device.index);
        ImGui::TableNextColumn();
        if (ImGui::Selectable(k4a_device->device.serial_number.c_str(), selected_device == i, ImGuiSelectableFlags_SpanAllColumns)){
          k4a_swarm->set_selected_device(k4a_device);
          selected_device = i;
        }
        ImGui::PopID();
      }
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void Capture::configuration_depth(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  ImGui::Checkbox("Depth enabled", &k4a_device->depth.config.enabled);
  if(k4a_device->depth.config.enabled){
    ImGui::Indent();
    if(ImGui::TreeNode("Depth configuration")){
      static int depth_mode = 1;
      if(ImGui::RadioButton("NFOV Binned", &depth_mode, 0)){
        k4a_device->depth.config.mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("NFOV Unbinned", &depth_mode, 1)){
        k4a_device->depth.config.mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
      }
      if(ImGui::RadioButton("WFOV Binned", &depth_mode, 2)){
        k4a_device->depth.config.mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("WFOV Unbinned", &depth_mode, 3)){
        k4a_device->depth.config.mode = K4A_DEPTH_MODE_WFOV_UNBINNED;
      }
      if(ImGui::RadioButton("Passive IR", &depth_mode, 4)){
        k4a_device->depth.config.mode = K4A_DEPTH_MODE_PASSIVE_IR;
      }

      ImGui::TreePop();
    }
    ImGui::Unindent();
  }

  //---------------------------
}
void Capture::configuration_color(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  ImGui::Checkbox("Color enabled", &k4a_device->color.config.enabled);
  if(k4a_device->color.config.enabled){
    ImGui::Indent();
    if(ImGui::TreeNode("Color configuration")){

      //Format
      ImGui::Text("Format");
      static int color_format = 0;
      if(ImGui::RadioButton("BGRA", &color_format, 0)){
        k4a_device->color.config.format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("MJPG", &color_format, 1)){
        k4a_device->color.config.format = K4A_IMAGE_FORMAT_COLOR_MJPG;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("NV12", &color_format, 2)){
        k4a_device->color.config.format = K4A_IMAGE_FORMAT_COLOR_NV12;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("YUY2", &color_format, 3)){
        k4a_device->color.config.format = K4A_IMAGE_FORMAT_COLOR_YUY2;
      }

      //Resolution
      ImGui::Text("Resolution [16:9]");
      ImGui::Indent();
      static int color_resolution = 0;
      if(ImGui::RadioButton("720p", &color_resolution, 0)){
        k4a_device->color.config.resolution = K4A_COLOR_RESOLUTION_720P;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("1080p", &color_resolution, 1)){
        k4a_device->color.config.resolution = K4A_COLOR_RESOLUTION_1080P;
      }
      if(ImGui::RadioButton("1440p", &color_resolution, 2)){
        k4a_device->color.config.resolution = K4A_COLOR_RESOLUTION_1440P;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("2160p", &color_resolution, 3)){
        k4a_device->color.config.resolution = K4A_COLOR_RESOLUTION_2160P;
      }
      ImGui::Unindent();

      ImGui::Text("Resolution [4:3]");
      ImGui::Indent();
      if(ImGui::RadioButton("1536p", &color_resolution, 4)){
        k4a_device->color.config.resolution = K4A_COLOR_RESOLUTION_1536P;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("3072p", &color_resolution, 5)){
        k4a_device->color.config.resolution = K4A_COLOR_RESOLUTION_3072P;
      }
      ImGui::Unindent();

      ImGui::TreePop();
    }

    if(ImGui::TreeNode("Color control")){
      //Exposur time
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Exposure Time", &k4a_device->color.config.exposure.value, 488, 1000000, "%d us");

      //White Balance
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("White Balance", &k4a_device->color.config.white_balance.value, 2500, 12500, "%d K");

      //Brightness
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Brightness", &k4a_device->color.config.brightness.value, 0, 255, "%d");

      //Contrast
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Contrast", &k4a_device->color.config.contrast.value, 0, 10, "%d");

      //Saturation
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Saturation", &k4a_device->color.config.saturation.value, 0, 63, "%d");

      //Sharpness
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Sharpness", &k4a_device->color.config.sharpness.value, 0, 4, "%d");

      //Gain
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Gain", &k4a_device->color.config.gain.value, 0, 255, "%d");

      //Backlight Compensation
      ImGui::Checkbox("Backlight Compensation", &k4a_device->color.config.backlight_compensation.value);

      //Power frequency
      ImGui::Text("Power Frequency");
      static int power_frequency = 0;
      if(ImGui::RadioButton("50Hz", &power_frequency, 0)){
        k4a_device->color.config.power_frequency.value = 1;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("60Hz", &power_frequency, 1)){
        k4a_device->color.config.power_frequency.value = 2;
      }

      //Refresh / reset buttons
      if (ImGui::Button("Restart")){
        k4a_device->restart_capture();
      }
      ImGui::SameLine();
      if (ImGui::Button("Reset to default##RGB")){
        k4a_device->reset_color_configuration();
      }

      ImGui::TreePop();
    }

    ImGui::Unindent();
  }

  //---------------------------
}
void Capture::configuration_device(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  static int framerate = 0;
  if(ImGui::RadioButton("30 FPS", &framerate, 0)){
    k4a_device->device.fps_mode = K4A_FRAMES_PER_SECOND_30;
    k4a_device->restart_capture();
  }
  ImGui::SameLine();
  if(ImGui::RadioButton("15 FPS", &framerate, 1)){
    k4a_device->device.fps_mode = K4A_FRAMES_PER_SECOND_15;
    k4a_device->restart_capture();
  }
  ImGui::SameLine();
  if(ImGui::RadioButton("5 FPS", &framerate, 2)){
    k4a_device->device.fps_mode = K4A_FRAMES_PER_SECOND_5;
    k4a_device->restart_capture();
  }

  if(ImGui::Checkbox("Disable streaming LED", &k4a_device->synchro.disable_streaming_indicator)){
    k4a_device->restart_capture();
  }

  //---------------------------
}
void Capture::firmware_info(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  if(k4a_device == nullptr) return;
  //---------------------------

  if (ImGui::TreeNode("Device Firmware Version Info")){
    k4a_hardware_version_t versionInfo = k4a_device->device.version;
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

}
