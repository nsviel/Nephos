#include "Stream.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <Utility/Node/Namespace.h>
#include <Engine/Capture/K4A/Device/K4A_swarm.h>


namespace gui::kinect{

//Constructor / Destructor
Stream::Stream(GUI* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::capture::Node* node_capture = engine->get_node_capture();

  this->kinect = node_capture->get_kinect();
  this->k4a_depth = new eng::kinect::data::Depth();
  this->k4a_infrared = new eng::kinect::data::Infrared();
  this->k4a_swarm = kinect->get_k4a_swarm();
  this->gui = gui;

  this->vec_gui_stream.push_back(new gui::media::Stream(gui));
  this->vec_gui_stream.push_back(new gui::media::Stream(gui));
  this->vec_gui_stream.push_back(new gui::media::Stream(gui));
  this->vec_gui_stream.push_back(new gui::media::Stream(gui));

  //---------------------------
}
Stream::~Stream(){}

//Main function
void Stream::run_panel(){
  K4A_device* k4a_device = k4a_swarm->get_selected_device();
  //---------------------------

  if(*show_window && k4a_device != nullptr){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Stream::design_panel(){
  //---------------------------

  this->vec_device_tab();

  //---------------------------
}

//All devices
void Stream::vec_device_tab(){
  list<K4A_device*>& list_device = k4a_swarm->get_list_device();
  //---------------------------

  if(ImGui::BeginTabBar("devices_tab##4567")){
    for(int i=0; i<list_device.size(); i++){
      K4A_device* k4a_device = *std::next(list_device.begin(), i);

      if(ImGui::BeginTabItem(k4a_device->device.name.c_str(), NULL)){
        this->device_tab(k4a_device);
        ImGui::EndTabItem();
      }

    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
void Stream::device_tab(K4A_device* k4a_device){
  if(!k4a_device->device.data_ready){return;}
  //---------------------------

  //Display capture images
  if(ImGui::BeginTabBar("device_tab##4567")){
    ImVec2 image_size = ImGui::GetContentRegionAvail();

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("All##4567", NULL)){
      image_size = ImVec2(image_size.x, image_size.y/3-3.33);
      this->draw_camera_color(k4a_device, image_size);
      this->draw_camera_depth(k4a_device, image_size);
      this->draw_camera_ir(k4a_device, image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Color##4567", NULL)){
      this->draw_camera_color(k4a_device, image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Color from depth##4567", NULL)){
      this->draw_camera_color_from_depth(k4a_device, image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Depth##4567", NULL)){
      this->draw_camera_depth(k4a_device, image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("IR##4567", NULL)){
      this->draw_camera_ir(k4a_device, image_size);
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Device capture windows
void Stream::draw_camera_color(K4A_device* k4a_device, ImVec2 image_size){
  eng::kinect::structure::Image* data_color = &k4a_device->color.image;
  //---------------------------

  eng::data::Image struct_image;
  struct_image.data = data_color->data;
  struct_image.width = data_color->width;
  struct_image.height = data_color->height;
  struct_image.format = data_color->format;

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[0]->draw_stream(&struct_image, image_size);
  this->overlay_capture(k4a_device, data_color, image_size, image_pose);

  //---------------------------
}
void Stream::draw_camera_color_from_depth(K4A_device* k4a_device, ImVec2 image_size){
  eng::kinect::structure::Image* data_color = &k4a_device->color.image_depth;
  //---------------------------

  //Il y a un probleme ici non identifié, le vecteur semble changer de taille (?)
  /*int size = k4a_device->color.image_depth.data.size();
  for(int i=0; i<k4a_device->color.image_depth.data.size(); i++){
    if(float(k4a_device->color.image_depth.data[i]) != 255.0f){
      say("nop");
      say(float(k4a_device->color.image_depth.data[i]));
    }

  }*/

  eng::data::Image struct_image;
  struct_image.data = data_color->data;
  struct_image.width = data_color->width;
  struct_image.height = data_color->height;
  struct_image.format = data_color->format;

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[3]->draw_stream(&struct_image, image_size);
  this->overlay_capture(k4a_device, data_color, image_size, image_pose);

  //---------------------------
}
void Stream::draw_camera_depth(K4A_device* k4a_device, ImVec2 image_size){
  eng::kinect::structure::Image* data_depth = &k4a_device->depth.image;
  //---------------------------

  std::vector<uint8_t> new_buffer = k4a_depth->convert_depth_into_color(k4a_device);

  eng::data::Image struct_image;
  struct_image.data = new_buffer;
  struct_image.width = data_depth->width;
  struct_image.height = data_depth->height;
  struct_image.format = "R8G8B8A8_SRGB";

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[1]->draw_stream(&struct_image, image_size);
  this->overlay_capture(k4a_device, data_depth, image_size, image_pose);

  //---------------------------
}
void Stream::draw_camera_ir(K4A_device* k4a_device, ImVec2 image_size){
  eng::kinect::structure::Image* data_ir = &k4a_device->ir.image;
  //---------------------------

  std::vector<uint8_t> new_buffer = k4a_infrared->convert_ir_into_color(k4a_device);

  eng::data::Image struct_image;
  struct_image.data = new_buffer;
  struct_image.width = data_ir->width;
  struct_image.height = data_ir->height;
  struct_image.format = "B8G8R8A8_SRGB";

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[2]->draw_stream(&struct_image, image_size);
  this->overlay_capture(k4a_device, data_ir, image_size, image_pose);

  //---------------------------
}

//Overlay
void Stream::overlay_capture(K4A_device* k4a_device, eng::kinect::structure::Image* image, ImVec2 image_size, ImVec2 image_pose){
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
  flags |= ImGuiWindowFlags_NoDocking;

  if (ImGui::Begin(image->name.c_str(), nullptr, flags)){
    this->overlay_information(k4a_device, image);
    this->overlay_pixel(image, image_size);
  }
  ImGui::End();

  //---------------------------
}
void Stream::overlay_information(K4A_device* k4a_device, eng::kinect::structure::Image* image){
  //---------------------------

  ImGui::Text("Frame rate: %.2f fps", k4a_device->device.fps);
  ImGui::Text("Timestamp: %.2f s", image->timestamp);
  if(image->temperature != -1){
    ImGui::Text("Temperature: %.2f°", image->temperature);
  }

  //---------------------------
}
void Stream::overlay_pixel(eng::kinect::structure::Image* image, ImVec2 image_size){
  //---------------------------

  if(image->hovered_pixel_x != -1 && image->hovered_pixel_y != -1){
    ImGui::Text("Hovered pixel: %.0f %.0f", image->hovered_pixel_x, image->hovered_pixel_y);
    ImGui::Text("Hovered pixel: %.3f", image->hovered_pixel_m);
  }

  //---------------------------
}
void Stream::compute_hovered_pixel(eng::kinect::structure::Image* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered){
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
    const std::vector<uint8_t>& data = image->data;
    size_t index = size_t(image->hovered_pixel_y) * size_t(image->width * 2) + size_t(image->hovered_pixel_x * 2);
    uint16_t pixelData = static_cast<uint16_t>(data[index]) | (static_cast<uint16_t>(data[index + 1]) << 8);
    image->hovered_pixel_m = pixelData / 1000.0f;
  }

  //---------------------------
}


}
