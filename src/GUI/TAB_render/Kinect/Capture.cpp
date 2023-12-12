#include "Capture.h"

#include <Node/GUI.h>
#include <Utility/Node/Namespace.h>
#include <Utility/Capture/Kinect/Device/K4A_swarm.h>


namespace gui::kinect{

//Constructor / Destructor
Capture::Capture(GUI* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------

  util::Node* utility = gui->get_utility();
  util::capture::Node* utl_capture = utility->get_utl_capture();

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

      string str_virtual = device->device.is_virtual ? "virtual_" : "";
      string title = "kinect_" + str_virtual + to_string(device->device.index);

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
  if(!device->device.data_ready){return;}
  //---------------------------

  //Close device button
  if(!device->device.is_virtual){
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
  util::kinect::structure::Image* data_color = &device->color.image;
  //---------------------------

  util::base::Image struct_image;
  struct_image.buffer = data_color->buffer;
  struct_image.width = data_color->width;
  struct_image.height = data_color->height;
  struct_image.format = data_color->format;


  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[0]->draw_stream(&struct_image, image_size);
  this->overlay_capture(data_color, image_size, image_pose);

  //---------------------------
}
void Capture::draw_camera_depth(K4A_device* device, ImVec2 image_size){
  util::kinect::structure::Image* data_depth = &device->depth.image;
  //---------------------------

  uint8_t* new_buffer = k4a_depth->convert_depth_into_color(device);

  util::base::Image struct_image;
  struct_image.buffer = new_buffer;
  struct_image.width = data_depth->width;
  struct_image.height = data_depth->height;
  struct_image.format = "R8G8B8A8_SRGB";

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[1]->draw_stream(&struct_image, image_size);
  this->overlay_capture(data_depth, image_size, image_pose);

  delete[] new_buffer;

  //---------------------------
}
void Capture::draw_camera_ir(K4A_device* device, ImVec2 image_size){
  util::kinect::structure::Image* data_ir = &device->ir.image;
  //---------------------------

  uint8_t* new_buffer = k4a_infrared->convert_ir_into_color(device);

  util::base::Image struct_image;
  struct_image.buffer = new_buffer;
  struct_image.width = data_ir->width;
  struct_image.height = data_ir->height;
  struct_image.format = "B8G8R8A8_SRGB";

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[2]->draw_stream(&struct_image, image_size);
  this->overlay_capture(data_ir, image_size, image_pose);

  delete[] new_buffer;

  //---------------------------
}

//Overlay
void Capture::overlay_capture(util::kinect::structure::Image* image, ImVec2 image_size, ImVec2 image_pose){
  //---------------------------

  //Hovered pixel
  bool image_hovered = ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenOverlappedByWindow);
  this->compute_hovered_pixel(image, image_size, image_pose, image_hovered);

  //Overlay
  ImGui::SetNextWindowPos(image_pose, ImGuiCond_Always);
  ImGui::SetNextWindowBgAlpha(0.3f);
  ImGuiWindowFlags flags;
  flags |= ImGuiWindowFlags_NoMove;
  flags |= ImGuiWindowFlags_NoTitleBar;
  flags |= ImGuiWindowFlags_NoResize;
  flags |= ImGuiWindowFlags_AlwaysAutoResize;
  flags |= ImGuiWindowFlags_NoSavedSettings;
  flags |= ImGuiWindowFlags_NoFocusOnAppearing;
  flags |= ImGuiWindowFlags_NoNav;
  flags |= ImGuiWindowFlags_NoNavFocus;
  flags |= ImGuiWindowFlags_NoScrollbar;

  if (ImGui::Begin(image->name.c_str(), nullptr, flags)){
    this->overlay_information(image);
    this->overlay_pixel(image, image_size);
  }
  ImGui::End();

  //---------------------------
}
void Capture::overlay_information(util::kinect::structure::Image* image){
  //---------------------------

  ImGui::Text("Average frame rate: %.2f fps", 5.0);
  ImGui::Text("Timestamp: %.2f s", image->timestamp);
  if(image->temperature != -1){
    ImGui::Text("Temperature: %.2f°", image->temperature);
  }

  //---------------------------
}
void Capture::overlay_pixel(util::kinect::structure::Image* image, ImVec2 image_size){
  //---------------------------

  if(image->hovered_pixel_x != -1 && image->hovered_pixel_y != -1){
    ImGui::Text("Hovered pixel: %.0f %.0f", image->hovered_pixel_x, image->hovered_pixel_y);
    ImGui::Text("Hovered pixel: %.3f", image->hovered_pixel_m);
  }

  //---------------------------
}
void Capture::compute_hovered_pixel(util::kinect::structure::Image* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered){
  //---------------------------

  //Reinitialize coord values
  image->hovered_pixel_x = -1;
  image->hovered_pixel_y = -1;

  // Compute hovered pixel coordinates
  if(image_hovered && (image->name == "depth" || image->name == "ir")){
    ImVec2 mousePos = ImGui::GetIO().MousePos;
    ImVec2 hoveredUIPixel;
    ImVec2 sourceImageDimensions = ImVec2(image->width, image->height);
    hoveredUIPixel.x = mousePos.x - image_pose.x;
    hoveredUIPixel.x = std::min(hoveredUIPixel.x, image_size.x);
    hoveredUIPixel.x = std::max(hoveredUIPixel.x, 0.0f);

    hoveredUIPixel.y = mousePos.y - image_pose.y;
    hoveredUIPixel.y = std::min(hoveredUIPixel.y, image_size.y);
    hoveredUIPixel.y = std::max(hoveredUIPixel.y, 0.0f);

    const float uiCoordinateToImageCoordinateRatio = sourceImageDimensions.x / image_size.x;

    image->hovered_pixel_x = hoveredUIPixel.x * uiCoordinateToImageCoordinateRatio;
    image->hovered_pixel_y = hoveredUIPixel.y * uiCoordinateToImageCoordinateRatio;

    //Pixel value
    uint16_t* buffer = reinterpret_cast<uint16_t*>(image->buffer);
    image->hovered_pixel_m = buffer[size_t(image->hovered_pixel_y) * size_t(image->width) + size_t(image->hovered_pixel_x)] / 1000.0f;
  }

  //---------------------------
}

}
