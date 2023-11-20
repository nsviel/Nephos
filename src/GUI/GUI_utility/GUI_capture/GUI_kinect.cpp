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
    ImGui::Unindent();
  }

  //Color parameters
  ImGui::Checkbox("Color enabled", &device.config.enable_camera_color);
  if(device.config.enable_camera_color){
    ImGui::Indent();

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
    ImGui::Text("Resolution - 16:9");
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

    ImGui::Text("Resolution - 4:3");
    ImGui::Indent();
    if(ImGui::RadioButton("1536p", &color_resolution, 4)){
      device.config.color_resolution = K4A_COLOR_RESOLUTION_1536P;
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("3072p", &color_resolution, 5)){
      device.config.color_resolution = K4A_COLOR_RESOLUTION_3072P;
    }
    ImGui::Unindent();

    ImGui::Unindent();
  }






/*
if (ImGui::TreeNode("Color Controls"))
{
    // Some of the variable names in here are just long enough to cause clang-format to force a line-wrap,
    // which causes half of these (very similar) calls to look radically different than the rest, which
    // makes it harder to pick out similarities/differences at a glance, so turn off clang-format for this
    // bit.
    //
    // clang-format off

    const float SliderScaleFactor = 0.5f;

    ShowColorControl(K4A_COLOR_CONTROL_EXPOSURE_TIME_ABSOLUTE, &m_colorSettingsCache.ExposureTimeUs,
        [SliderScaleFactor](ColorSetting *cacheEntry) {
            ColorControlAction result = ColorControlAction::None;

            // Exposure time supported values are factors off 1,000,000 / 2, so we need an exponential control.
            // There isn't one for ints, so we use the float control and make it look like an int control.
            //
            auto valueFloat = static_cast<float>(cacheEntry->Value);
            ImGui::PushItemWidth(ImGui::CalcItemWidth() * SliderScaleFactor);
            if (ImGuiExtensions::K4ASliderFloat("Exposure Time",
                                                &valueFloat,
                                                488.f,
                                                1000000.f,
                                                "%.0f us",
                                                8.0f,
                                                cacheEntry->Mode == K4A_COLOR_CONTROL_MODE_MANUAL))
            {
                result = ColorControlAction::SetManual;
                cacheEntry->Value = static_cast<int32_t>(valueFloat);
            }
            ImGui::PopItemWidth();

            ImGui::SameLine();
            ShowColorControlAutoButton(cacheEntry->Mode, &result, "exposure");
            return result;
    });

    ShowColorControl(K4A_COLOR_CONTROL_WHITEBALANCE, &m_colorSettingsCache.WhiteBalance,
        [SliderScaleFactor](ColorSetting *cacheEntry) {
            ColorControlAction result = ColorControlAction::None;
            ImGui::PushItemWidth(ImGui::CalcItemWidth() * SliderScaleFactor);
            if (ImGuiExtensions::K4ASliderInt("White Balance",
                                              &cacheEntry->Value,
                                              2500,
                                              12500,
                                              "%d K",
                                              cacheEntry->Mode == K4A_COLOR_CONTROL_MODE_MANUAL))
            {
                result = ColorControlAction::SetManual;

                // White balance must be stepped in units of 10 or the call to update the setting fails.
                //
                cacheEntry->Value -= cacheEntry->Value % 10;
            }
            ImGui::PopItemWidth();

            ImGui::SameLine();
            ShowColorControlAutoButton(cacheEntry->Mode, &result, "whitebalance");
            return result;
    });

    ImGui::PushItemWidth(ImGui::CalcItemWidth() * SliderScaleFactor);

    ShowColorControl(K4A_COLOR_CONTROL_BRIGHTNESS, &m_colorSettingsCache.Brightness,
        [](ColorSetting *cacheEntry) {
            return ImGui::SliderInt("Brightness", &cacheEntry->Value, 0, 255) ?
                ColorControlAction::SetManual :
                ColorControlAction::None;
    });

    ShowColorControl(K4A_COLOR_CONTROL_CONTRAST, &m_colorSettingsCache.Contrast,
        [](ColorSetting *cacheEntry) {
            return ImGui::SliderInt("Contrast", &cacheEntry->Value, 0, 10) ?
                ColorControlAction::SetManual :
                ColorControlAction::None;
    });

    ShowColorControl(K4A_COLOR_CONTROL_SATURATION, &m_colorSettingsCache.Saturation,
        [](ColorSetting *cacheEntry) {
            return ImGui::SliderInt("Saturation", &cacheEntry->Value, 0, 63) ?
                ColorControlAction::SetManual :
                ColorControlAction::None;
    });

    ShowColorControl(K4A_COLOR_CONTROL_SHARPNESS, &m_colorSettingsCache.Sharpness,
        [](ColorSetting *cacheEntry) {
            return ImGui::SliderInt("Sharpness", &cacheEntry->Value, 0, 4) ?
                ColorControlAction::SetManual :
                ColorControlAction::None;
    });

    ShowColorControl(K4A_COLOR_CONTROL_GAIN, &m_colorSettingsCache.Gain,
        [](ColorSetting *cacheEntry) {
            return ImGui::SliderInt("Gain", &cacheEntry->Value, 0, 255) ?
                ColorControlAction::SetManual :
                ColorControlAction::None;
    });

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
