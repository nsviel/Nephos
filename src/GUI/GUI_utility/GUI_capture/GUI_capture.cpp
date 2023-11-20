#include "GUI_capture.h"

#include <GUI_gpu/GUI_video.h>
#include <GUI_gpu/GUI_image.h>
#include <TAB_render/TAB_render.h>
#include <UTL_capture/UTL_v4l2/UTL_device.h>
#include <UTL_capture/UTL_capture.h>
#include <GUI.h>


//Constructor / Destructor
GUI_capture::GUI_capture(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->gui_image = new GUI_image(gui);
  this->gui_video = new GUI_video(gui);
  this->gui = gui;
  this->utl_device = new UTL_device();
  this->utl_capture = new UTL_capture();

  this->stream_node = "";

  //---------------------------
}
GUI_capture::~GUI_capture(){}

//Main function
void GUI_capture::design_panel(){
  //---------------------------

  this->capture_devices();
  this->capture_command();
  this->truc();
  utl_capture->truc();

  //---------------------------
}

//Subfunction
void GUI_capture::capture_devices(){
  //---------------------------

  utl_device->find_video_devices();
  vector<Struct_video_device> vec_devices = utl_device->get_vec_video_device();

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;
  static int selected_device = -1;
  if (ImGui::BeginTable("database_view", 2, flags)) {
    for (int i = 0; i < vec_devices.size(); i++) {
      Struct_video_device& device = vec_devices[i];

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      ImGui::PushID(device.name.c_str());

      // Use ImGui::Selectable to make the row selectable
      if (ImGui::Selectable(device.name.c_str(), selected_device == i, ImGuiSelectableFlags_SpanAllColumns)) {
        this->stream_node = device.node;
        gui_video->restart_video();
        selected_device = i;
      }

      ImGui::TableNextColumn();
      ImGui::Text("%s", device.node.c_str());

      ImGui::PopID();
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void GUI_capture::capture_command(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  gui_video->draw_video(stream_node);
  //gui_image->draw_image_static("../media/vulkano.jpg");

  //---------------------------
}
void GUI_capture::truc(){
  //---------------------------






  //---------------------------
}
