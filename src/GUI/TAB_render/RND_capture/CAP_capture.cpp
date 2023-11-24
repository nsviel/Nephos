#include "CAP_capture.h"

#include <GUI.h>
#include <GUI_gpu/GUI_stream.h>
#include <Utility.h>
#include <UTL_capture/UTL_capture.h>
#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_swarm.h>
#include <UTL_capture/UTL_kinect/K4A_data/K4A_depth.h>
#include <UTL_capture/UTL_kinect/K4A_data/K4A_infrared.h>


//Constructor / Destructor
CAP_capture::CAP_capture(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Utility* utility = gui->get_utility();
  UTL_capture* utl_capture = utility->get_utl_capture();

  this->kinect = utl_capture->get_kinect();
  this->struct_k4a_swarm = kinect->get_struct_kinect();
  this->k4a_depth = new K4A_depth();
  this->k4a_infrared = new K4A_infrared();
  this->gui = gui;

  this->vec_gui_stream.push_back(new GUI_stream(gui));
  this->vec_gui_stream.push_back(new GUI_stream(gui));
  this->vec_gui_stream.push_back(new GUI_stream(gui));

  //---------------------------
}
CAP_capture::~CAP_capture(){}

//Main function
void CAP_capture::design_panel(){
  //---------------------------

  this->vec_device_tab();

  //---------------------------
}

//All devices
void CAP_capture::vec_device_tab(){
  vector<K4A_device*>& vec_device = struct_k4a_swarm->vec_device;
  //---------------------------

  if(ImGui::BeginTabBar("devices_tab##4567")){
    for(int i=0; i<vec_device.size(); i++){
      K4A_device* device = vec_device[i];

      string title = "kinect_" + to_string(device->index);
      if (ImGui::BeginTabItem(title.c_str(), NULL)){
        this->device_tab(device);
        ImGui::EndTabItem();
      }

    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
void CAP_capture::device_tab(K4A_device* device){
  if(!device->data.data_ready){return;}
  //---------------------------

  if(ImGui::BeginTabBar("device_tab##4567")){
    ImVec2 image_size = ImGui::GetContentRegionAvail();

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("All##4567", NULL)){
      image_size = ImVec2(image_size.x, image_size.y/3-3.33);
      this->draw_camera_color(device, image_size);
      this->draw_camera_depth(device, image_size);
      this->draw_camera_ir(device, image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Color##4567", NULL)){
      this->draw_camera_color(device, image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Depth##4567", NULL)){
      this->draw_camera_depth(device, image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("IR##4567", NULL)){
      this->draw_camera_ir(device, image_size);
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Device capture windows
void CAP_capture::draw_camera_color(K4A_device* device, ImVec2 image_size){
  K4A_image* k4a_image = &device->data.color;
  //---------------------------

  Struct_image struct_image;
  struct_image.buffer = k4a_image->buffer;
  struct_image.width = k4a_image->width;
  struct_image.height = k4a_image->height;
  struct_image.format = k4a_image->format;

  this->hovered_info_panel(k4a_image);
  vec_gui_stream[0]->draw_stream(&struct_image, image_size);

  //---------------------------
}
void CAP_capture::draw_camera_depth(K4A_device* device, ImVec2 image_size){
  K4A_image* k4a_image = &device->data.depth;
  //---------------------------

  Struct_image struct_image;
  struct_image.buffer = k4a_depth->convert_depth_into_color(device);
  struct_image.width = k4a_image->width;
  struct_image.height = k4a_image->height;
  struct_image.format = "R8G8B8A8_SRGB";

  this->hovered_info_panel(k4a_image);
  vec_gui_stream[1]->draw_stream(&struct_image, image_size);

  //---------------------------
}
void CAP_capture::draw_camera_ir(K4A_device* device, ImVec2 image_size){
  K4A_image* k4a_image = &device->data.ir;
  //---------------------------

  Struct_image struct_image;
  struct_image.buffer = k4a_infrared->convert_ir_into_color(device);
  struct_image.width = k4a_image->width;
  struct_image.height = k4a_image->height;
  struct_image.format = "B8G8R8A8_SRGB";

  this->hovered_info_panel(k4a_image);
  vec_gui_stream[2]->draw_stream(&struct_image, image_size);

  //---------------------------
}
void CAP_capture::hovered_info_panel(K4A_image* image){
  //---------------------------

  ImVec2 imageStartPos = ImGui::GetCursorScreenPos();
  ImGui::SetNextWindowPos(imageStartPos, ImGuiCond_Always);
  ImGui::SetNextWindowBgAlpha(0.3f);
  ImGuiWindowFlags flags;
  flags |= ImGuiWindowFlags_NoMove;
  flags |= ImGuiWindowFlags_NoTitleBar;
  flags |= ImGuiWindowFlags_NoResize;
  flags |= ImGuiWindowFlags_AlwaysAutoResize;
  flags |= ImGuiWindowFlags_NoSavedSettings;
  flags |= ImGuiWindowFlags_NoFocusOnAppearing;
  flags |= ImGuiWindowFlags_NoNav;
  flags |= ImGuiWindowFlags_NoScrollbar;

  if (ImGui::Begin(image->name.c_str(), nullptr, flags)){
    ImGui::Text("Average frame rate: %.2f fps", 5.0);
    ImGui::Text("Timestamp: %.2f", image->timestamp/1000);
  }
  ImGui::End();

  ImGui::SetCursorScreenPos(imageStartPos);

  //---------------------------
}
