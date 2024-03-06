#include "Capture.h"

#include <K4N/Namespace.h>
#include <Scene/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Capture::Capture(k4n::Node* node_k4n){
  //---------------------------

  this->node_k4n = node_k4n;
  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->k4n_config = new k4n::config::Configuration();
  this->sce_set = new eng::scene::Set();

  this->item_width = 100;

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::show_master_capture(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------

  this->list_device(master);
  ImGui::Separator();
  if(ImGui::TreeNode("Capture")){
    this->configuration_depth(master);
    this->configuration_color(master);
    this->configuration_color_control(master);
    this->configuration_fps(master);
    this->configuration_button(master);

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}

//Subfunction
void Capture::list_device(k4n::dev::Master* master){
  if(master->mode == k4n::dev::PLAYBACK) return;
  //---------------------------

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;
  static int selected_device = -1;
  if(ImGui::BeginTable("database_view", 3, flags)){
    if(k4n_swarm->get_list_master().size() == 0){
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
      for(int i=0; i<master->list_entity.size(); i++){
        utl::type::Entity* entity = *next(master->list_entity.begin(), i);

        if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
          ImGui::TableNextRow();
          ImGui::TableNextColumn();

          ImGui::PushID(sensor->param.serial_number.c_str());
          ImGui::Text("Azur Kinect");
          ImGui::TableNextColumn();
          ImGui::Text("%d", sensor->param.index);
          ImGui::TableNextColumn();
          if (ImGui::Selectable(sensor->param.serial_number.c_str(), selected_device == i, ImGuiSelectableFlags_SpanAllColumns)){
            sce_set->select_entity(master, sensor);
            selected_device = i;
          }
          ImGui::PopID();
        }
      }
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void Capture::configuration_depth(k4n::dev::Master* master){
  //---------------------------

  ImGui::Checkbox("Depth enabled", &master->config.depth.enabled);
  if(master->config.depth.enabled){
    ImGui::Indent();
    if(ImGui::TreeNode("Depth configuration")){
      int depth_mode = master->config.depth.mode;
      if(ImGui::RadioButton("NFOV Binned", &depth_mode, K4A_DEPTH_MODE_NFOV_2X2BINNED)){
        master->config.depth.mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("NFOV Unbinned", &depth_mode, K4A_DEPTH_MODE_NFOV_UNBINNED)){
        master->config.depth.mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
      }
      if(ImGui::RadioButton("WFOV Binned", &depth_mode, K4A_DEPTH_MODE_WFOV_2X2BINNED)){
        master->config.depth.mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("WFOV Unbinned", &depth_mode, K4A_DEPTH_MODE_WFOV_UNBINNED)){
        master->config.depth.mode = K4A_DEPTH_MODE_WFOV_UNBINNED;
        if(master->config.fps.mode == K4A_FRAMES_PER_SECOND_30){
          master->config.fps.mode = K4A_FRAMES_PER_SECOND_15;
        }
      }
      if(ImGui::RadioButton("Passive IR", &depth_mode, K4A_DEPTH_MODE_PASSIVE_IR)){
        master->config.depth.mode = K4A_DEPTH_MODE_PASSIVE_IR;
      }

      ImGui::TreePop();
    }
    ImGui::Unindent();
  }

  //---------------------------
}
void Capture::configuration_color(k4n::dev::Master* master){
  //---------------------------

  ImGui::Checkbox("Color enabled", &master->config.color.enabled);
  if(master->config.color.enabled){
    ImGui::Indent();
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

    ImGui::Unindent();
  }

  //---------------------------
}
void Capture::configuration_color_control(k4n::dev::Master* master){
  //---------------------------

  if(master->config.color.enabled){
    ImGui::Indent();
    if(ImGui::TreeNode("Color control")){

      if(ImGui::BeginTable("truc##color_control", 2)){
        //Exposure time
        ImGui::TableNextRow(); ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(100);
        if(ImGui::SliderInt("Exposure Time", &master->config.color.exposure.value, 488, 1000000, "%d us")){
          master->manage_color_control();
        }
        ImGui::TableNextColumn();
        switch(master->config.color.exposure.mode){
          case K4A_COLOR_CONTROL_MODE_MANUAL:{
            if(ImGui::Button("M##Exposure")){
              master->config.color.exposure.mode = K4A_COLOR_CONTROL_MODE_AUTO;
              master->manage_color_control();
            }
            break;
          }
          case K4A_COLOR_CONTROL_MODE_AUTO:{
            if(ImGui::Button("A##Exposure")){
              master->config.color.exposure.mode = K4A_COLOR_CONTROL_MODE_MANUAL;
              master->manage_color_control();
            }
            break;
          }
        }

        //White balance
        ImGui::TableNextRow(); ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(100);
        if(ImGui::SliderInt("White Balance", &master->config.color.white_balance.value, 2500, 12500, "%d K")){
          master->manage_color_control();
        }
        ImGui::TableNextColumn();
        switch(master->config.color.white_balance.mode){
          case K4A_COLOR_CONTROL_MODE_MANUAL:{
            if(ImGui::Button("M##Balance")){
              master->config.color.white_balance.mode = K4A_COLOR_CONTROL_MODE_AUTO;
              master->manage_color_control();
            }
            break;
          }
          case K4A_COLOR_CONTROL_MODE_AUTO:{
            if(ImGui::Button("A##Balance")){
              master->config.color.white_balance.mode = K4A_COLOR_CONTROL_MODE_MANUAL;
              master->manage_color_control();
            }
            break;
          }
        }

        ImGui::EndTable();
      }

      //Brightness
      ImGui::SetNextItemWidth(100);
      if(ImGui::SliderInt("Brightness", &master->config.color.brightness.value, 0, 255, "%d")){
        master->manage_color_control();
      }

      //Contrast
      ImGui::SetNextItemWidth(100);
      if(ImGui::SliderInt("Contrast", &master->config.color.contrast.value, 0, 10, "%d")){
        master->manage_color_control();
      }

      //Saturation
      ImGui::SetNextItemWidth(100);
      if(ImGui::SliderInt("Saturation", &master->config.color.saturation.value, 0, 63, "%d")){
        master->manage_color_control();
      }

      //Sharpness
      ImGui::SetNextItemWidth(100);
      if(ImGui::SliderInt("Sharpness", &master->config.color.sharpness.value, 0, 4, "%d")){
        master->manage_color_control();
      }

      //Gain
      ImGui::SetNextItemWidth(100);
      if(ImGui::SliderInt("Gain", &master->config.color.gain.value, 0, 255, "%d")){
        master->manage_color_control();
      }

      //Backlight Compensation
      if(ImGui::Checkbox("Backlight Compensation", &master->config.color.backlight_compensation.value)){
        master->manage_color_control();
      }

      //Power frequency
      ImGui::Text("Power Frequency");
      if(ImGui::RadioButton("50Hz", &master->config.color.power_frequency.value, 1)){
        master->manage_color_control();
      }
      ImGui::SameLine();
      if(ImGui::RadioButton("60Hz", &master->config.color.power_frequency.value, 2)){
        master->manage_color_control();
      }

      ImGui::TreePop();
    }

    ImGui::Unindent();
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

  /*if(ImGui::Checkbox("Disable streaming LED", &sensor->synchro.disable_streaming_indicator)){

  }*/

  //---------------------------
}
void Capture::configuration_button(k4n::dev::Master* master){
  //---------------------------

  //Refresh / reset buttons
  if(ImGui::Button("Restart")){
    master->reset();
  }
  ImGui::SameLine();
  if(ImGui::Button("Reset to default##RGB")){
    k4n_config->make_master_configuration_initial(master);
  }

  //---------------------------
}


}
