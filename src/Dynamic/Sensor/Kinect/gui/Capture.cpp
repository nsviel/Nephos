#include "Capture.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Capture::Capture(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_capture = new k4n::capture::Capture(node_k4n);
  this->k4n_config = new k4n::capture::Configuration(node_k4n);
  this->k4n_struct = node_k4n->get_k4n_structure();

  this->item_width = 100;

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::show_info(k4n::capture::Sensor& sensor){
  //---------------------------

  //Table
  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Sensor");
  ImGui::BeginTable("sensor##info", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 75.0f);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);

  //Recording time
  if(sensor.state.record){
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Record"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f s", sensor.timestamp.record);
  }
/*
  //Recording file size
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Size"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%.2f Mo", master->recorder.file_size);

  //Size
  if(player->size != 0){
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Size"); ImGui::TableNextColumn();
    ImGui::TextColored(color, "%.2f Mo", player->size);
  }
*/
  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Capture::show_parameter(k4n::capture::Sensor& sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Transformation");
  this->show_transformation_mode();

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Configuration");
  this->configuration_depth();
  this->configuration_color();
  this->configuration_camera();
  this->configuration_fps();
  this->configuration_synchro();
  this->configuration_button();

  //---------------------------
  ImGui::Separator();
}

//Subfunction
void Capture::show_transformation_mode(){
  //---------------------------

  ImGui::RadioButton("Depth to color", &k4n_struct->transformation.mode, k4n::transformation::DEPTH_TO_COLOR);
  ImGui::SameLine();
  ImGui::RadioButton("Color to depth", &k4n_struct->transformation.mode, k4n::transformation::COLOR_TO_DEPTH);

  //---------------------------
  ImGui::Separator();
}
void Capture::show_firmware_info(k4n::capture::Sensor& sensor){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Device Firmware Version Info");

  ImVec4 color = ImVec4(54/255.0f, 125/255.0f, 155/255.0f, 1.0f);
  ImGui::BeginTable("device##firmware", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 150.0f);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("RGB camera"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.firmware.color.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Depth camera"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.firmware.depth.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Audio"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.firmware.audio.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Build config"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.firmware.build.c_str());

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Signature type"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "%s", sensor.firmware.constructor.c_str());

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Capture::configuration_depth(){
  //---------------------------

  if(ImGui::TreeNode("Depth")){
    ImGui::SeparatorText("Depth");

    int depth_mode = k4n_struct->config.depth.mode;
    if(ImGui::RadioButton("NFOV Binned 2x2", &depth_mode, K4A_DEPTH_MODE_NFOV_2X2BINNED)){
      k4n_struct->config.depth.mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
    }
    ImGui::SetItemTooltip("[320 x 288] resolution");
    ImGui::SameLine();
    if(ImGui::RadioButton("NFOV Unbinned", &depth_mode, K4A_DEPTH_MODE_NFOV_UNBINNED)){
      k4n_struct->config.depth.mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
    }
    ImGui::SetItemTooltip("[640 x 576] resolution");
    if(ImGui::RadioButton("WFOV Binned 2x2", &depth_mode, K4A_DEPTH_MODE_WFOV_2X2BINNED)){
      k4n_struct->config.depth.mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
    }
    ImGui::SetItemTooltip("[512 x 512] resolution");
    ImGui::SameLine();
    if(ImGui::RadioButton("WFOV Unbinned", &depth_mode, K4A_DEPTH_MODE_WFOV_UNBINNED)){
      k4n_struct->config.depth.mode = K4A_DEPTH_MODE_WFOV_UNBINNED;
      if(k4n_struct->fps.mode == K4A_FRAMES_PER_SECOND_30){
        k4n_struct->fps.mode = K4A_FRAMES_PER_SECOND_15;
      }
    }
    ImGui::SetItemTooltip("[1024 x 1024] resolution");
    if(ImGui::RadioButton("Passive IR", &depth_mode, K4A_DEPTH_MODE_PASSIVE_IR)){
      k4n_struct->config.depth.mode = K4A_DEPTH_MODE_PASSIVE_IR;
    }
    ImGui::SetItemTooltip("[1024 x 1024] resolution");

    ImGui::TreePop();
  }

  //---------------------------
}
void Capture::configuration_color(){
  //---------------------------

  if(ImGui::TreeNode("Color")){
    ImGui::SeparatorText("Color");

    //Format
    ImGui::Text("Format");
    int color_format = k4n_struct->config.color.format;
    if(ImGui::RadioButton("BGRA", &color_format, K4A_IMAGE_FORMAT_COLOR_BGRA32)){
      k4n_struct->config.color.format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
      if(k4n_struct->config.color.resolution == K4A_COLOR_RESOLUTION_720P){
        k4n_struct->config.color.resolution = K4A_COLOR_RESOLUTION_1080P;
      }
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("MJPG", &color_format, K4A_IMAGE_FORMAT_COLOR_MJPG)){
      k4n_struct->config.color.format = K4A_IMAGE_FORMAT_COLOR_MJPG;
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("NV12", &color_format, K4A_IMAGE_FORMAT_COLOR_NV12)){
      k4n_struct->config.color.format = K4A_IMAGE_FORMAT_COLOR_NV12;
      if(k4n_struct->config.color.resolution == K4A_COLOR_RESOLUTION_1080P ||
        k4n_struct->config.color.resolution == K4A_COLOR_RESOLUTION_1440P ||
        k4n_struct->config.color.resolution == K4A_COLOR_RESOLUTION_2160P){
        k4n_struct->config.color.resolution = K4A_COLOR_RESOLUTION_720P;
      }
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("YUY2", &color_format, K4A_IMAGE_FORMAT_COLOR_YUY2)){
      k4n_struct->config.color.format = K4A_IMAGE_FORMAT_COLOR_YUY2;
    }

    //Resolution
    ImGui::Text("Resolution [16:9]");
    ImGui::Indent();
    int color_resolution = k4n_struct->config.color.resolution;

    bool condition = (k4n_struct->config.color.format == K4A_IMAGE_FORMAT_COLOR_BGRA32);
    if(condition) ImGui::BeginDisabled();
    if(ImGui::RadioButton("720p", &color_resolution, K4A_COLOR_RESOLUTION_720P)){
      k4n_struct->config.color.resolution = K4A_COLOR_RESOLUTION_720P;
    }
    if(condition) ImGui::EndDisabled();

    condition = (k4n_struct->config.color.format == K4A_IMAGE_FORMAT_COLOR_NV12 || k4n_struct->config.color.format == K4A_IMAGE_FORMAT_COLOR_YUY2);
    if(condition) ImGui::BeginDisabled();
    ImGui::SameLine();
    if(ImGui::RadioButton("1080p", &color_resolution, K4A_COLOR_RESOLUTION_1080P)){
      k4n_struct->config.color.resolution = K4A_COLOR_RESOLUTION_1080P;
    }
    if(ImGui::RadioButton("1440p", &color_resolution, K4A_COLOR_RESOLUTION_1440P)){
      k4n_struct->config.color.resolution = K4A_COLOR_RESOLUTION_1440P;
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("2160p", &color_resolution, K4A_COLOR_RESOLUTION_2160P)){
      k4n_struct->config.color.resolution = K4A_COLOR_RESOLUTION_2160P;
    }
    ImGui::Unindent();

    ImGui::Text("Resolution [4:3]");
    ImGui::Indent();
    if(ImGui::RadioButton("1536p", &color_resolution, K4A_COLOR_RESOLUTION_1536P)){
      k4n_struct->config.color.resolution = K4A_COLOR_RESOLUTION_1536P;
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("3072p", &color_resolution, K4A_COLOR_RESOLUTION_3072P)){
      k4n_struct->config.color.resolution = K4A_COLOR_RESOLUTION_3072P;
      if(k4n_struct->fps.mode == K4A_FRAMES_PER_SECOND_30){
        k4n_struct->fps.mode = K4A_FRAMES_PER_SECOND_15;
      }
    }
    if(condition) ImGui::EndDisabled();

    ImGui::Unindent();
    ImGui::TreePop();
  }

  //---------------------------
}
void Capture::configuration_camera(){
  //---------------------------

  if(ImGui::TreeNode("Camera")){
    ImGui::SeparatorText("Camera");

    ImGui::BeginTable("truc##color_control", 2);
    //Exposure time
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(100);
    float exposure_value = (float)k4n_struct->config.color.exposure.value;
    if(ImGui::SliderFloat("Exposure Time", &exposure_value, 488.0f, 1000000.0f, "%.0f us", ImGuiSliderFlags_Logarithmic)){
      k4n_struct->config.color.exposure.value = exposure_value;
      k4n_capture->manage_configuration();
    }
    ImGui::TableNextColumn();
    switch(k4n_struct->config.color.exposure.mode){
      case K4A_COLOR_CONTROL_MODE_MANUAL:{
        if(ImGui::Button("M##Exposure")){
          k4n_struct->config.color.exposure.mode = K4A_COLOR_CONTROL_MODE_AUTO;
          k4n_capture->manage_configuration();
        }
        break;
      }
      case K4A_COLOR_CONTROL_MODE_AUTO:{
        if(ImGui::Button("A##Exposure")){
          k4n_struct->config.color.exposure.mode = K4A_COLOR_CONTROL_MODE_MANUAL;
          k4n_capture->manage_configuration();
        }
        break;
      }
    }

    //White balance
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(100);
    if(ImGui::SliderInt("White Balance", &k4n_struct->config.color.white_balance.value, 2500, 12500, "%d K")){
      k4n_capture->manage_configuration();
    }
    ImGui::TableNextColumn();
    switch(k4n_struct->config.color.white_balance.mode){
      case K4A_COLOR_CONTROL_MODE_MANUAL:{
        if(ImGui::Button("M##Balance")){
          k4n_struct->config.color.white_balance.mode = K4A_COLOR_CONTROL_MODE_AUTO;
          k4n_capture->manage_configuration();
        }
        break;
      }
      case K4A_COLOR_CONTROL_MODE_AUTO:{
        if(ImGui::Button("A##Balance")){
          k4n_struct->config.color.white_balance.mode = K4A_COLOR_CONTROL_MODE_MANUAL;
          k4n_capture->manage_configuration();
        }
        break;
      }
    }

    ImGui::EndTable();

    //Brightness
    ImGui::SetNextItemWidth(100);
    if(ImGui::SliderInt("Brightness", &k4n_struct->config.color.brightness.value, 0, 255, "%d")){
      k4n_capture->manage_configuration();
    }

    //Contrast
    ImGui::SetNextItemWidth(100);
    if(ImGui::SliderInt("Contrast", &k4n_struct->config.color.contrast.value, 0, 10, "%d")){
      k4n_capture->manage_configuration();
    }

    //Saturation
    ImGui::SetNextItemWidth(100);
    if(ImGui::SliderInt("Saturation", &k4n_struct->config.color.saturation.value, 0, 63, "%d")){
      k4n_capture->manage_configuration();
    }

    //Sharpness
    ImGui::SetNextItemWidth(100);
    if(ImGui::SliderInt("Sharpness", &k4n_struct->config.color.sharpness.value, 0, 4, "%d")){
      k4n_capture->manage_configuration();
    }

    //Gain
    ImGui::SetNextItemWidth(100);
    if(ImGui::SliderInt("Gain", &k4n_struct->config.color.gain.value, 0, 255, "%d")){
      k4n_capture->manage_configuration();
    }

    //Backlight Compensation
    if(ImGui::Checkbox("Backlight Compensation", &k4n_struct->config.color.backlight_compensation.value)){
      k4n_capture->manage_configuration();
    }

    //Power frequency
    ImGui::Text("Power Frequency");
    if(ImGui::RadioButton("50Hz", &k4n_struct->config.color.power_frequency.value, 1)){
      k4n_capture->manage_configuration();
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("60Hz", &k4n_struct->config.color.power_frequency.value, 2)){
      k4n_capture->manage_configuration();
    }

    ImGui::TreePop();
  }

  //---------------------------
}
void Capture::configuration_fps(){
  int framerate = k4n_struct->fps.mode;
  //---------------------------

  if(ImGui::TreeNode("FPS")){
    ImGui::SeparatorText("FPS");

    bool condition = (k4n_struct->config.depth.mode == K4A_DEPTH_MODE_WFOV_UNBINNED || k4n_struct->config.color.resolution == K4A_COLOR_RESOLUTION_3072P);
    if(condition) ImGui::BeginDisabled();
    if(ImGui::RadioButton("30 FPS", &framerate, K4A_FRAMES_PER_SECOND_30)){
      k4n_struct->fps.mode = K4A_FRAMES_PER_SECOND_30;
    }
    if(condition) ImGui::EndDisabled();

    ImGui::SameLine();
    if(ImGui::RadioButton("15 FPS", &framerate, K4A_FRAMES_PER_SECOND_15)){
      k4n_struct->fps.mode = K4A_FRAMES_PER_SECOND_15;
    }

    ImGui::SameLine();
    if(ImGui::RadioButton("5 FPS", &framerate, K4A_FRAMES_PER_SECOND_5)){
      k4n_struct->fps.mode = K4A_FRAMES_PER_SECOND_5;
    }

    ImGui::TreePop();
  }

  //---------------------------
}
void Capture::configuration_synchro(){
  //---------------------------

  if(ImGui::TreeNode("Synchro")){
    ImGui::SeparatorText("Synchro");

    //Streaming front LED
    ImGui::Checkbox("Disable streaming LED", &k4n_struct->config.synchro.disable_streaming_indicator);

    //Synchronized images only
    ImGui::Checkbox("Synchronized images only", &k4n_struct->config.synchro.synchronized_images_only);

    //Depth delay
    ImGui::SetNextItemWidth(100);
    ImGui::InputScalar("Depth delay (us)", ImGuiDataType_U32, &k4n_struct->config.synchro.depth_delay_off_color_us, NULL, NULL, "%u");

    ImGui::TreePop();
  }

  //---------------------------
}
void Capture::configuration_button(){
  //---------------------------

  //Refresh / reset buttons
  if(ImGui::Button("Restart")){
    k4n_capture->manage_configuration();
    //set->reset();
  }
  ImGui::SameLine();
  if(ImGui::Button("Reset to default##RGB")){
    k4n_config->make_default_configuration();
  }

  //---------------------------
}


}
