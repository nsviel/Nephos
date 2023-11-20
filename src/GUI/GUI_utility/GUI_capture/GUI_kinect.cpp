#include "GUI_kinect.h"

#include <GUI.h>
#include <GUI_gpu/GUI_stream.h>
#include <UTL_capture/UTL_kinect/Kinect.h>
#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>


//Constructor / Destructor
GUI_kinect::GUI_kinect(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->gui = gui;
  this->kinect = new Kinect();
  this->struct_kinect = kinect->get_struct_kinect();
  this->k4a_device = new K4A_device(struct_kinect);
  this->gui_stream = new GUI_stream(gui);

  this->item_width = 100;

  //---------------------------
}
GUI_kinect::~GUI_kinect(){}

//Main function
void GUI_kinect::design_panel(){
  //---------------------------

  this->kinect_devices();
  this->configuration_device();
  this->configuration_general();
  this->draw_camera_color();

  //---------------------------
}

//Kinect device
void GUI_kinect::kinect_devices(){
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
void GUI_kinect::configuration_device(){
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
  ImGui::Separator();

  this->configuration_depth();
  this->configuration_color();

  //---------------------------
}
void GUI_kinect::configuration_depth(){
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
void GUI_kinect::configuration_color(){
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
void GUI_kinect::configuration_general(){
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
void GUI_kinect::draw_camera_color(){
  Struct_k4a_device* device = struct_kinect->selected_device;
  if(device == nullptr) return;
  //---------------------------

  if(!device->is_capturing){return;}
  if(!device->capture->is_valid()){return;}
  k4a::image color_image = device->capture->get_color_image();
  //k4a::image color_image = device->capture->get_ir_image();
  //k4a::image color_image = device->capture->get_depth_image();
  if(!color_image.is_valid()){return;}

  uint8_t* color_data = color_image.get_buffer();
  int width = color_image.get_width_pixels();
  int height = color_image.get_height_pixels();
  gui_stream->draw_video(color_data, width, height);

  color_image.reset();

  //---------------------------
}
