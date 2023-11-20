#include "GUI_kinect.h"

#include <GUI.h>
#include <UTL_capture/UTL_kinect/Kinect.h>
#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_device.h>


//Constructor / Destructor
GUI_kinect::GUI_kinect(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->gui = gui;
  this->kinect = new Kinect();
  this->struct_kinect = kinect->get_struct_kinect();
  this->k4a_device = new K4A_device(struct_kinect);

  this->item_width = 100;

  //---------------------------
}
GUI_kinect::~GUI_kinect(){}

//Main function
void GUI_kinect::design_panel(){
  //---------------------------

  this->kinect_devices();
  this->kinect_configuration();

  //---------------------------
}

//Subfunction
void GUI_kinect::kinect_devices(){
  //---------------------------

  vector<Struct_k4a_device>& vec_device = struct_kinect->vec_device;

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;
  static int selected_device = -1;
  if(ImGui::BeginTable("database_view", 2, flags)){
    if(vec_device.size() == 0){
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::TableNextColumn();
      ImGui::Text("(No available devices)");
    }
    else{
      ImGui::TableSetupColumn("Index");
      ImGui::TableSetupColumn("Serial number");
      ImGui::TableHeadersRow();
      for(int i=0; i<vec_device.size(); i++){
        Struct_k4a_device& device = vec_device[i];

        ImGui::TableNextRow();
        ImGui::TableNextColumn();

        ImGui::PushID(device.serial_number.c_str());
        ImGui::Text("%d", device.index);
        ImGui::TableNextColumn();
        if (ImGui::Selectable(device.serial_number.c_str(), selected_device == i, ImGuiSelectableFlags_SpanAllColumns)){
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
void GUI_kinect::kinect_configuration(){
  Struct_k4a_device& device = struct_kinect->vec_device[0];
  //---------------------------

  ImGui::Separator();
  string device_header = "Device S/N: " + device.serial_number;
  ImGui::Text("%s", device_header.c_str());
  ImGui::SameLine();{
    if(ImGui::Button("Close", ImVec2(item_width, 0))){
    }
  }
  ImGui::Separator();

  //Depth parameters
  ImGui::Checkbox("Depth enabled", &device.config.enable_camera_depth);
  if(device.config.enable_camera_depth){
    ImGui::Indent();
    if(ImGui::TreeNode("Depth configuration")){
      static int depth_mode = 1;
      if(ImGui::RadioButton("NFOV Binned", &depth_mode, 0)){
        device.config.depth_mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("NFOV Unbinned", &depth_mode, 1)){
        device.config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
      }
      if(ImGui::RadioButton("WFOV Binned", &depth_mode, 2)){
        device.config.depth_mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("WFOV Unbinned", &depth_mode, 3)){
        device.config.depth_mode = K4A_DEPTH_MODE_WFOV_UNBINNED;
      }
      if(ImGui::RadioButton("Passive IR", &depth_mode, 4)){
        device.config.depth_mode = K4A_DEPTH_MODE_PASSIVE_IR;
      }

      ImGui::TreePop();
    }
    ImGui::Unindent();
  }

  //Color parameters
  ImGui::Checkbox("Color enabled", &device.config.enable_camera_color);
  if(device.config.enable_camera_color){
    ImGui::Indent();
    if(ImGui::TreeNode("Color configuration")){

      //Format
      ImGui::Text("Format");
      static int color_format = 0;
      if(ImGui::RadioButton("BGRA", &color_format, 0)){
        device.config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("MJPG", &color_format, 1)){
        device.config.color_format = K4A_IMAGE_FORMAT_COLOR_MJPG;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("NV12", &color_format, 2)){
        device.config.color_format = K4A_IMAGE_FORMAT_COLOR_NV12;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("YUY2", &color_format, 3)){
        device.config.color_format = K4A_IMAGE_FORMAT_COLOR_YUY2;
      }

      //Resolution
      ImGui::Text("Resolution [16:9]");
      ImGui::Indent();
      static int color_resolution = 0;
      if(ImGui::RadioButton("720p", &color_resolution, 0)){
        device.config.color_resolution = K4A_COLOR_RESOLUTION_720P;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("1080p", &color_resolution, 1)){
        device.config.color_resolution = K4A_COLOR_RESOLUTION_1080P;
      }
      if(ImGui::RadioButton("1440p", &color_resolution, 2)){
        device.config.color_resolution = K4A_COLOR_RESOLUTION_1440P;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("2160p", &color_resolution, 3)){
        device.config.color_resolution = K4A_COLOR_RESOLUTION_2160P;
      }
      ImGui::Unindent();

      ImGui::Text("Resolution [4:3]");
      ImGui::Indent();
      if(ImGui::RadioButton("1536p", &color_resolution, 4)){
        device.config.color_resolution = K4A_COLOR_RESOLUTION_1536P;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("3072p", &color_resolution, 5)){
        device.config.color_resolution = K4A_COLOR_RESOLUTION_3072P;
      }
      ImGui::Unindent();

      ImGui::TreePop();
    }

    if(ImGui::TreeNode("Color control")){
      //Exposur time
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Exposure Time", &device.config.color.exposure_time_us, 488, 1000000, "%d us");

      //White Balance
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("White Balance", &device.config.color.white_balance, 2500, 12500, "%d K");

      //Brightness
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Brightness", &device.config.color.brightness, 0, 255, "%d");

      //Contrast
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Contrast", &device.config.color.contrast, 0, 10, "%d");

      //Saturation
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Saturation", &device.config.color.saturation, 0, 63, "%d");

      //Sharpness
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Sharpness", &device.config.color.sharpness, 0, 4, "%d");

      //Gain
      ImGui::SetNextItemWidth(100);
      ImGui::SliderInt("Gain", &device.config.color.gain, 0, 255, "%d");




      ImGui::TreePop();
    }

    ImGui::Unindent();
  }




/*
if (ImGui::TreeNode("Color Controls"))
{
    ImGui::PopItemWidth();

    ShowColorControl(K4A_COLOR_CONTROL_BACKLIGHT_COMPENSATION, &m_colorSettingsCache.BacklightCompensation,
        [](ColorSetting *cacheEntry) {
            return ImGui::Checkbox("Backlight Compensation", reinterpret_cast<bool *>(&cacheEntry->Value)) ?
                ColorControlAction::SetManual :
                ColorControlAction::None;
     });

    ShowColorControl(K4A_COLOR_CONTROL_POWERLINE_FREQUENCY, &m_colorSettingsCache.PowerlineFrequency,
        [](ColorSetting *cacheEntry) {
            ImGui::Text("Power Frequency");
            ImGui::SameLine();
            bool updated = false;
            updated |= ImGui::RadioButton("50Hz", &cacheEntry->Value, 1);
            ImGui::SameLine();
            updated |= ImGui::RadioButton("60Hz", &cacheEntry->Value, 2);
            return updated ? ColorControlAction::SetManual : ColorControlAction::None;
     });

    // clang-format on

    if (ImGui::Button("Refresh"))
    {
        LoadColorSettingsCache();
    }

    ImGui::SameLine();

    if (ImGui::Button("Reset to default##RGB"))
    {
        ApplyDefaultColorSettings();
    }

    ImGui::TreePop();
}
*/

  //---------------------------
}
