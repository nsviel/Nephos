#include "Capture.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Capture::Capture(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();

  this->node_k4n = node_k4n;
  this->k4n_config = new k4n::utils::Configuration();
  this->dat_set = node_data->get_dat_set();

  this->item_width = 100;

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::show_parameter(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  this->show_list_device(master);
  this->show_transformation_mode(master);

  ImGui::SetNextItemWidth(75);
  if(ImGui::BeginTabItem("Capture##566", NULL)){
    this->configuration_synchro(master);
    this->configuration_depth(master);
    this->configuration_color(master);
    this->configuration_color_control(master);
    this->configuration_fps(master);
    this->configuration_button(master);

    ImGui::Separator();
    ImGui::EndTabItem();
  }

  //---------------------------
}

//Subfunction
void Capture::show_list_device(k4n::dev::Master* master){
  //---------------------------

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;
  ImGui::BeginTable("database_view", 4, flags);

  if(master->list_entity.size() == 0){
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TableNextColumn();
    ImGui::Text("(No devices)");
  }
  else{
    ImGui::TableSetupColumn("");
    ImGui::TableSetupColumn("ID");
    ImGui::TableSetupColumn("Serial number", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 20);
    ImGui::TableHeadersRow();
    for(int i=0; i<master->list_entity.size(); i++){
      dat::base::Entity* entity = *next(master->list_entity.begin(), i);

      if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
        ImGui::PushID(sensor->device.serial_number.c_str());

        //Sensor type
        ImGui::TableNextRow(); ImGui::TableNextColumn();
        ImGui::Text("Azur Kinect");

        //Sensor ID
        ImGui::TableNextColumn();
        ImGui::Text("%d", sensor->device.idx_dev);

        //Sensor serial number
        ImGui::TableNextColumn();
        ImGui::Text("%s", sensor->device.serial_number.c_str());

        //Sensor capture or not
        ImGui::TableNextColumn();
        if(sensor->is_thread_running()){
          ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 100, 100, 255));
          ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(180, 100, 100, 255));
          if(ImGui::SmallButton("X##399")){
            sensor->stop_thread();
          }
          ImGui::PopStyleColor(2);
        }else{
          ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(100, 133, 100, 255));
          ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 180, 100, 255));
          if(ImGui::SmallButton(ICON_FA_PLAY "##399")){
            sensor->run_thread();
          }
          ImGui::PopStyleColor(2);
        }

        ImGui::PopID();
      }
    }
  }

  ImGui::EndTable();

  //---------------------------
}
void Capture::show_transformation_mode(k4n::dev::Master* master){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Transformation");

  ImGui::RadioButton("Depth to color", &master->config.depth.transformation_mode, k4n::depth::DEPTH_TO_COLOR);
  ImGui::SameLine();
  ImGui::RadioButton("Color to depth", &master->config.depth.transformation_mode, k4n::depth::COLOR_TO_DEPTH);

  //---------------------------
  ImGui::Separator();
}
void Capture::show_firmware_info(k4n::dev::Sensor* sensor){
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
void Capture::configuration_depth(k4n::dev::Master* master){
  //---------------------------

  if(ImGui::TreeNode("Depth configuration")){
    int depth_mode = master->config.depth.mode;
    if(ImGui::RadioButton("NFOV Binned 2x2", &depth_mode, K4A_DEPTH_MODE_NFOV_2X2BINNED)){
      master->config.depth.mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
    }
    ImGui::SetItemTooltip("[320 x 288] resolution");
    ImGui::SameLine();
    if(ImGui::RadioButton("NFOV Unbinned", &depth_mode, K4A_DEPTH_MODE_NFOV_UNBINNED)){
      master->config.depth.mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
    }
    ImGui::SetItemTooltip("[640 x 576] resolution");
    if(ImGui::RadioButton("WFOV Binned 2x2", &depth_mode, K4A_DEPTH_MODE_WFOV_2X2BINNED)){
      master->config.depth.mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
    }
    ImGui::SetItemTooltip("[512 x 512] resolution");
    ImGui::SameLine();
    if(ImGui::RadioButton("WFOV Unbinned", &depth_mode, K4A_DEPTH_MODE_WFOV_UNBINNED)){
      master->config.depth.mode = K4A_DEPTH_MODE_WFOV_UNBINNED;
      if(master->config.fps.mode == K4A_FRAMES_PER_SECOND_30){
        master->config.fps.mode = K4A_FRAMES_PER_SECOND_15;
      }
    }
    ImGui::SetItemTooltip("[1024 x 1024] resolution");
    if(ImGui::RadioButton("Passive IR", &depth_mode, K4A_DEPTH_MODE_PASSIVE_IR)){
      master->config.depth.mode = K4A_DEPTH_MODE_PASSIVE_IR;
    }
    ImGui::SetItemTooltip("[1024 x 1024] resolution");

    ImGui::TreePop();
  }

  //---------------------------
}
void Capture::configuration_color(k4n::dev::Master* master){
  //---------------------------

  if(ImGui::TreeNode("Color configuration")){

    //Format
    ImGui::Text("Format");
    int color_format = master->config.color.format;
    if(ImGui::RadioButton("BGRA", &color_format, K4A_IMAGE_FORMAT_COLOR_BGRA32)){
      master->config.color.format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
      if(master->config.color.resolution == K4A_COLOR_RESOLUTION_720P){
        master->config.color.resolution = K4A_COLOR_RESOLUTION_1080P;
      }
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("MJPG", &color_format, K4A_IMAGE_FORMAT_COLOR_MJPG)){
      master->config.color.format = K4A_IMAGE_FORMAT_COLOR_MJPG;
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("NV12", &color_format, K4A_IMAGE_FORMAT_COLOR_NV12)){
      master->config.color.format = K4A_IMAGE_FORMAT_COLOR_NV12;
      if(master->config.color.resolution == K4A_COLOR_RESOLUTION_1080P ||
        master->config.color.resolution == K4A_COLOR_RESOLUTION_1440P ||
        master->config.color.resolution == K4A_COLOR_RESOLUTION_2160P){
        master->config.color.resolution = K4A_COLOR_RESOLUTION_720P;
      }
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("YUY2", &color_format, K4A_IMAGE_FORMAT_COLOR_YUY2)){
      master->config.color.format = K4A_IMAGE_FORMAT_COLOR_YUY2;
    }

    //Resolution
    ImGui::Text("Resolution [16:9]");
    ImGui::Indent();
    int color_resolution = master->config.color.resolution;

    bool condition = (master->config.color.format == K4A_IMAGE_FORMAT_COLOR_BGRA32);
    if(condition) ImGui::BeginDisabled();
    if(ImGui::RadioButton("720p", &color_resolution, K4A_COLOR_RESOLUTION_720P)){
      master->config.color.resolution = K4A_COLOR_RESOLUTION_720P;
    }
    if(condition) ImGui::EndDisabled();

    condition = (master->config.color.format == K4A_IMAGE_FORMAT_COLOR_NV12 || master->config.color.format == K4A_IMAGE_FORMAT_COLOR_YUY2);
    if(condition) ImGui::BeginDisabled();
    ImGui::SameLine();
    if(ImGui::RadioButton("1080p", &color_resolution, K4A_COLOR_RESOLUTION_1080P)){
      master->config.color.resolution = K4A_COLOR_RESOLUTION_1080P;
    }
    if(ImGui::RadioButton("1440p", &color_resolution, K4A_COLOR_RESOLUTION_1440P)){
      master->config.color.resolution = K4A_COLOR_RESOLUTION_1440P;
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("2160p", &color_resolution, K4A_COLOR_RESOLUTION_2160P)){
      master->config.color.resolution = K4A_COLOR_RESOLUTION_2160P;
    }
    ImGui::Unindent();

    ImGui::Text("Resolution [4:3]");
    ImGui::Indent();
    if(ImGui::RadioButton("1536p", &color_resolution, K4A_COLOR_RESOLUTION_1536P)){
      master->config.color.resolution = K4A_COLOR_RESOLUTION_1536P;
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("3072p", &color_resolution, K4A_COLOR_RESOLUTION_3072P)){
      master->config.color.resolution = K4A_COLOR_RESOLUTION_3072P;
      if(master->config.fps.mode == K4A_FRAMES_PER_SECOND_30){
        master->config.fps.mode = K4A_FRAMES_PER_SECOND_15;
      }
    }
    if(condition) ImGui::EndDisabled();

    ImGui::Unindent();
    ImGui::TreePop();
  }

  //---------------------------
}
void Capture::configuration_color_control(k4n::dev::Master* master){
  dyn::base::Player* player = &master->player;
  //---------------------------

  if(ImGui::TreeNode("Color control")){

    ImGui::BeginTable("truc##color_control", 2);
    //Exposure time
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(100);
    float exposure_value = (float)master->config.color.exposure.value;
    if(ImGui::SliderFloat("Exposure Time", &exposure_value, 488.0f, 1000000.0f, "%.0f us", ImGuiSliderFlags_Logarithmic)){
      master->config.color.exposure.value = exposure_value;
      player->manage_configuration();
    }
    ImGui::TableNextColumn();
    switch(master->config.color.exposure.mode){
      case K4A_COLOR_CONTROL_MODE_MANUAL:{
        if(ImGui::Button("M##Exposure")){
          master->config.color.exposure.mode = K4A_COLOR_CONTROL_MODE_AUTO;
          player->manage_configuration();
        }
        break;
      }
      case K4A_COLOR_CONTROL_MODE_AUTO:{
        if(ImGui::Button("A##Exposure")){
          master->config.color.exposure.mode = K4A_COLOR_CONTROL_MODE_MANUAL;
          player->manage_configuration();
        }
        break;
      }
    }

    //White balance
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(100);
    if(ImGui::SliderInt("White Balance", &master->config.color.white_balance.value, 2500, 12500, "%d K")){
      player->manage_configuration();
    }
    ImGui::TableNextColumn();
    switch(master->config.color.white_balance.mode){
      case K4A_COLOR_CONTROL_MODE_MANUAL:{
        if(ImGui::Button("M##Balance")){
          master->config.color.white_balance.mode = K4A_COLOR_CONTROL_MODE_AUTO;
          player->manage_configuration();
        }
        break;
      }
      case K4A_COLOR_CONTROL_MODE_AUTO:{
        if(ImGui::Button("A##Balance")){
          master->config.color.white_balance.mode = K4A_COLOR_CONTROL_MODE_MANUAL;
          player->manage_configuration();
        }
        break;
      }
    }

    ImGui::EndTable();

    //Brightness
    ImGui::SetNextItemWidth(100);
    if(ImGui::SliderInt("Brightness", &master->config.color.brightness.value, 0, 255, "%d")){
      player->manage_configuration();
    }

    //Contrast
    ImGui::SetNextItemWidth(100);
    if(ImGui::SliderInt("Contrast", &master->config.color.contrast.value, 0, 10, "%d")){
      player->manage_configuration();
    }

    //Saturation
    ImGui::SetNextItemWidth(100);
    if(ImGui::SliderInt("Saturation", &master->config.color.saturation.value, 0, 63, "%d")){
      player->manage_configuration();
    }

    //Sharpness
    ImGui::SetNextItemWidth(100);
    if(ImGui::SliderInt("Sharpness", &master->config.color.sharpness.value, 0, 4, "%d")){
      player->manage_configuration();
    }

    //Gain
    ImGui::SetNextItemWidth(100);
    if(ImGui::SliderInt("Gain", &master->config.color.gain.value, 0, 255, "%d")){
      player->manage_configuration();
    }

    //Backlight Compensation
    if(ImGui::Checkbox("Backlight Compensation", &master->config.color.backlight_compensation.value)){
      player->manage_configuration();
    }

    //Power frequency
    ImGui::Text("Power Frequency");
    if(ImGui::RadioButton("50Hz", &master->config.color.power_frequency.value, 1)){
      player->manage_configuration();
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("60Hz", &master->config.color.power_frequency.value, 2)){
      player->manage_configuration();
    }

    ImGui::TreePop();
  }

  //---------------------------
}
void Capture::configuration_fps(k4n::dev::Master* master){
  int framerate = master->config.fps.mode;
  //---------------------------

  bool condition = (master->config.depth.mode == K4A_DEPTH_MODE_WFOV_UNBINNED || master->config.color.resolution == K4A_COLOR_RESOLUTION_3072P);
  if(condition) ImGui::BeginDisabled();
  if(ImGui::RadioButton("30 FPS", &framerate, K4A_FRAMES_PER_SECOND_30)){
    master->config.fps.mode = K4A_FRAMES_PER_SECOND_30;
  }
  if(condition) ImGui::EndDisabled();

  ImGui::SameLine();
  if(ImGui::RadioButton("15 FPS", &framerate, K4A_FRAMES_PER_SECOND_15)){
    master->config.fps.mode = K4A_FRAMES_PER_SECOND_15;
  }

  ImGui::SameLine();
  if(ImGui::RadioButton("5 FPS", &framerate, K4A_FRAMES_PER_SECOND_5)){
    master->config.fps.mode = K4A_FRAMES_PER_SECOND_5;
  }

  //---------------------------
}
void Capture::configuration_synchro(k4n::dev::Master* master){
  //---------------------------

  //Internal sync
  if(ImGui::TreeNode("Synchronization")){
    //Streaming front LED
    ImGui::Checkbox("Disable streaming LED", &master->config.synchro.disable_streaming_indicator);

    //Synchronized images only
    ImGui::Checkbox("Synchronized images only", &master->config.synchro.synchronized_images_only);

    //Depth delay
    ImGui::SetNextItemWidth(100);
    ImGui::InputScalar("Depth delay (us)", ImGuiDataType_U32, &master->config.synchro.depth_delay_off_color_us, NULL, NULL, "%u");

    ImGui::TreePop();
  }

  //---------------------------
}
void Capture::configuration_button(k4n::dev::Master* master){
  dyn::base::Player* player = &master->player;
  //---------------------------

  //Refresh / reset buttons
  if(ImGui::Button("Restart")){
    player->manage_configuration();
    master->reset();
  }
  ImGui::SameLine();
  if(ImGui::Button("Reset to default##RGB")){
    k4n_config->make_master_configuration_initial(master);
  }

  //---------------------------
}


}
