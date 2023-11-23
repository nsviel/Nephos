#include "CAP_capture.h"

#include <GUI.h>
#include <GUI_gpu/GUI_stream.h>
#include <Utility.h>
#include <UTL_capture/UTL_capture.h>
#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_data/K4A_depth.h>
#include <UTL_capture/UTL_kinect/K4A_data/K4A_infrared.h>


//Constructor / Destructor
CAP_capture::CAP_capture(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Utility* utility = gui->get_utility();
  UTL_capture* utl_capture = utility->get_utl_capture();

  this->kinect = utl_capture->get_kinect();
  this->struct_kinect = kinect->get_struct_kinect();
  this->k4a_depth = new K4A_depth(struct_kinect);
  this->k4a_infrared = new K4A_infrared(struct_kinect);
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

  if (ImGui::BeginTabBar("capture_tab")){
    ImVec2 image_size = ImGui::GetContentRegionAvail();

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("All##4567", NULL)){
      image_size = ImVec2(image_size.x, image_size.y/3);
      this->draw_camera_color(image_size);
      this->draw_camera_depth(image_size);
      this->draw_camera_ir(image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Color##4567", NULL)){
      this->draw_camera_color(image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Depth##4567", NULL)){
      this->draw_camera_depth(image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("IR##4567", NULL)){
      this->draw_camera_ir(image_size);
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}

//Subfunction
void CAP_capture::draw_camera_color(ImVec2 image_size){
  Struct_k4a_device* device = struct_kinect->selected_device;
  //---------------------------

  if(device == nullptr){return;}
  if(!device->data.data_ready){return;}
  say("---");

    
  K4A_image* k4a_image = &device->data.color;
  Struct_image struct_image;
  struct_image.buffer = k4a_image->buffer;
  struct_image.width = k4a_image->width;
  struct_image.height = k4a_image->height;
  struct_image.format = k4a_image->format;

  this->hovered_info_panel(k4a_image);
  vec_gui_stream[0]->draw_stream(&struct_image, image_size);

  //---------------------------
}
void CAP_capture::draw_camera_depth(ImVec2 image_size){
  Struct_k4a_device* device = struct_kinect->selected_device;
  //---------------------------

  if(device == nullptr){return;}
  if(!device->data.data_ready){return;}

  K4A_image* k4a_image = &device->data.depth;
  Struct_image struct_image;
  struct_image.buffer = k4a_depth->convert_depth_into_color(device);
  struct_image.width = k4a_image->width;
  struct_image.height = k4a_image->height;
  struct_image.format = "R8G8B8A8_SRGB";

  this->hovered_info_panel(k4a_image);
  vec_gui_stream[1]->draw_stream(&struct_image, image_size);

  //---------------------------
}
void CAP_capture::draw_camera_ir(ImVec2 image_size){
  Struct_k4a_device* device = struct_kinect->selected_device;
  //---------------------------

  if(device == nullptr){return;}
  if(!device->data.data_ready){return;}

  K4A_image* k4a_image = &device->data.ir;
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
