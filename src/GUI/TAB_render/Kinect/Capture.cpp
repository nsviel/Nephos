#include "Capture.h"

#include <Node/GUI.h>
#include <Utility/Node/Namespace.h>
#include <Utility/Capture/Kinect/K4A_device/K4A_swarm.h>


namespace gui::kinect{

//Constructor / Destructor
Capture::Capture(GUI* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------

  util::Node* utility = gui->get_utility();
  util::capture::Capture* utl_capture = utility->get_utl_capture();

  this->kinect = utl_capture->get_kinect();
  this->k4a_depth = new util::kinect::data::Depth();
  this->k4a_infrared = new util::kinect::data::Infrared();
  this->k4a_swarm = kinect->get_k4a_swarm();
  this->gui = gui;

  this->vec_gui_stream.push_back(new gui::media::Stream(gui));
  this->vec_gui_stream.push_back(new gui::media::Stream(gui));
  this->vec_gui_stream.push_back(new gui::media::Stream(gui));

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::design_panel(){
  //---------------------------

  this->vec_device_tab();

  //---------------------------
}

//All devices
void Capture::vec_device_tab(){
  list<K4A_device*>& list_device = kinect->get_list_device();
  //---------------------------

  if(ImGui::BeginTabBar("devices_tab##4567")){
    for(int i=0; i<list_device.size(); i++){
      K4A_device* device = *std::next(list_device.begin(), i);

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
void Capture::device_tab(K4A_device* device){
  if(!device->data.data_ready){return;}
  //---------------------------

  //Close device button
  if(!device->is_virtual){
    ImVec2 region = ImGui::GetContentRegionAvail();
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(133, 45, 45, 255));
    if(ImGui::Button("Close", ImVec2(region.x, 0))){
      k4a_swarm->delete_device(device);
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
void Capture::draw_camera_color(K4A_device* device, ImVec2 image_size){
  util::kinect::structure::K4A_image* data_color = &device->data.color;
  //---------------------------

  util::base::Image struct_image;
  struct_image.buffer = data_color->buffer;
  struct_image.width = data_color->width;
  struct_image.height = data_color->height;
  struct_image.format = data_color->format;

  this->hovered_info_panel(data_color);
  vec_gui_stream[0]->draw_stream(&struct_image, image_size);

  //---------------------------
}
void Capture::draw_camera_depth(K4A_device* device, ImVec2 image_size){
  util::kinect::structure::K4A_image* data_depth = &device->data.depth;
  //---------------------------

  uint8_t* new_buffer = k4a_depth->convert_depth_into_color(device);

  util::base::Image struct_image;
  struct_image.buffer = new_buffer;
  struct_image.width = data_depth->width;
  struct_image.height = data_depth->height;
  struct_image.format = "R8G8B8A8_SRGB";

  this->hovered_info_panel(data_depth);
  vec_gui_stream[1]->draw_stream(&struct_image, image_size);

  delete[] new_buffer;

  //---------------------------
}
void Capture::draw_camera_ir(K4A_device* device, ImVec2 image_size){
  util::kinect::structure::K4A_image* data_ir = &device->data.ir;
  //---------------------------

  uint8_t* new_buffer = k4a_infrared->convert_ir_into_color(device);

  util::base::Image struct_image;
  struct_image.buffer = new_buffer;
  struct_image.width = data_ir->width;
  struct_image.height = data_ir->height;
  struct_image.format = "B8G8R8A8_SRGB";

  this->hovered_info_panel(data_ir);
  vec_gui_stream[2]->draw_stream(&struct_image, image_size);

  delete[] new_buffer;

  //---------------------------
}
void Capture::hovered_info_panel(util::kinect::structure::K4A_image* image){
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

}
