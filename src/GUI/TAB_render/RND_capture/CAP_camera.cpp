#include "CAP_camera.h"

#include <GUI_gpu/GUI_stream.h>
#include <GUI_gpu/GUI_image.h>
#include <TAB_render/TAB_render.h>
#include <UTL_capture/UTL_v4l2/V4L2_device.h>
#include <UTL_capture/UTL_v4l2/V4L2_camera.h>
#include <UTL_capture/UTL_capture.h>
#include <GUI.h>


//Constructor / Destructor
CAP_camera::CAP_camera(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->gui = gui;
  this->gui_image = new GUI_image(gui);
  this->gui_stream = new GUI_stream(gui);
  this->v4l2_device = new V4L2_device();
  this->utl_capture = new UTL_capture();
  this->v4l2_stream = new V4L2_camera();

  this->stream_node = "";

  //---------------------------
}
CAP_camera::~CAP_camera(){}

//Main function
void CAP_camera::design_panel(){
  //---------------------------

  this->capture_devices();
  this->capture_command();

  //---------------------------
}

//Subfunction
void CAP_camera::capture_devices(){
  //---------------------------

  v4l2_device->find_video_devices();
  vector<Struct_video_device> vec_devices = v4l2_device->get_vec_video_device();

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
        v4l2_stream->clean_video();
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
void CAP_camera::capture_command(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  v4l2_stream->load_stream(stream_node);
  uint8_t* data = v4l2_stream->get_frame_data();
  int width = v4l2_stream->get_frame_width();
  int height = v4l2_stream->get_frame_height();
  gui_stream->draw_video(data, width, height);
  //gui_image->draw_image_static("../media/vulkano.jpg");

  //---------------------------
}
