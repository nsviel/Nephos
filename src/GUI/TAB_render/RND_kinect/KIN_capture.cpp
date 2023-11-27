#include "KIN_capture.h"

#include <GUI.h>
#include <GUI_gpu/GUI_stream.h>
#include <Utility.h>
#include <UTL_capture/UTL_capture.h>
#include <UTL_capture/UTL_kinect/K4A_data/K4A_depth.h>
#include <UTL_capture/UTL_kinect/K4A_data/K4A_infrared.h>


//Constructor / Destructor
KIN_capture::KIN_capture(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Utility* utility = gui->get_utility();
  UTL_capture* utl_capture = utility->get_utl_capture();

  this->kinect = utl_capture->get_kinect();
  this->k4a_depth = new K4A_depth();
  this->k4a_infrared = new K4A_infrared();
  this->gui = gui;

  this->vec_gui_stream.push_back(new GUI_stream(gui));
  this->vec_gui_stream.push_back(new GUI_stream(gui));
  this->vec_gui_stream.push_back(new GUI_stream(gui));

  //---------------------------
}
KIN_capture::~KIN_capture(){}

//Main function
void KIN_capture::design_panel(){
  //---------------------------

  this->vec_device_tab();

  //---------------------------
}

//All devices
void KIN_capture::vec_device_tab(){
  vector<K4A_device*>& vec_device = kinect->get_vec_device();
  //---------------------------

  if(ImGui::BeginTabBar("devices_tab##4567")){
    for(int i=0; i<vec_device.size(); i++){
      K4A_device* device = vec_device[i];

      string str_virtual = device->is_virtual ? "virtual_" : "";
      string title = "kinect_" + str_virtual + to_string(device->index);

      if(ImGui::BeginTabItem(title.c_str(), NULL)){
        this->device_tab(device);
        ImGui::EndTabItem();
      }

    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
void KIN_capture::device_tab(K4A_device* device){
  if(!device->data.data_ready){return;}
  //---------------------------

  //Close device button
  if(!device->is_virtual){
    ImVec2 region = ImGui::GetContentRegionAvail();
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if(ImGui::Button("Close", ImVec2(region.x, 0))){
      
    }
    ImGui::PopStyleColor(1);
  }

  //Display capture images
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
void KIN_capture::draw_camera_color(K4A_device* device, ImVec2 image_size){
  K4A_image* data_color = &device->data.color;
  //---------------------------

  Struct_image struct_image;
  struct_image.buffer = data_color->buffer;
  struct_image.width = data_color->width;
  struct_image.height = data_color->height;
  struct_image.format = data_color->format;

  this->hovered_info_panel(data_color);
  vec_gui_stream[0]->draw_stream(&struct_image, image_size);

  //---------------------------
}
void KIN_capture::draw_camera_depth(K4A_device* device, ImVec2 image_size){
  K4A_image* data_depth = &device->data.depth;
  //---------------------------

  uint8_t* new_buffer = k4a_depth->convert_depth_into_color(device);

  Struct_image struct_image;
  struct_image.buffer = new_buffer;
  struct_image.width = data_depth->width;
  struct_image.height = data_depth->height;
  struct_image.format = "R8G8B8A8_SRGB";

  this->hovered_info_panel(data_depth);
  vec_gui_stream[1]->draw_stream(&struct_image, image_size);

  delete[] new_buffer;

  //---------------------------
}
void KIN_capture::draw_camera_ir(K4A_device* device, ImVec2 image_size){
  K4A_image* data_ir = &device->data.ir;
  //---------------------------

  uint8_t* new_buffer = k4a_infrared->convert_ir_into_color(device);

  Struct_image struct_image;
  struct_image.buffer = new_buffer;
  struct_image.width = data_ir->width;
  struct_image.height = data_ir->height;
  struct_image.format = "B8G8R8A8_SRGB";

  this->hovered_info_panel(data_ir);
  vec_gui_stream[2]->draw_stream(&struct_image, image_size);

  delete[] new_buffer;

  //---------------------------
}
void KIN_capture::hovered_info_panel(K4A_image* image){
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
    ImGui::Text("Timestamp: %.2f s", image->timestamp/1000000);
  }
  ImGui::End();

  ImGui::SetCursorScreenPos(imageStartPos);

  //---------------------------
}
