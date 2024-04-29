#include "Stream.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Kinect/Namespace.h>
#include <Scene/Namespace.h>
#include <Vulkan/Namespace.h>
#include <GUI/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Stream::Stream(k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();

  this->node_k4n = node_k4n;
  this->k4n_swarm = node_k4n->get_k4n_swarm();
  this->sce_set = new sce::Set();

  this->vec_gui_stream.push_back(new gui_element::Stream(node_engine));
  this->vec_gui_stream.push_back(new gui_element::Stream(node_engine));
  this->vec_gui_stream.push_back(new gui_element::Stream(node_engine));
  this->vec_gui_stream.push_back(new gui_element::Stream(node_engine));

  this->show_window = show_window;
  this->name = "Stream";

  //---------------------------
}
Stream::~Stream(){}

//Main function
void Stream::run_panel(){
  k4n::dev::Master* master = k4n_swarm->get_selected_master();
  //---------------------------

  if(*show_window && master != nullptr && k4n_swarm->get_number_running_thread() != 0){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(100, 400), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(master);

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Stream::design_panel(k4n::dev::Master* master){
  //---------------------------

  this->vec_device_tab(master);

  //---------------------------
}

//All devices
void Stream::vec_device_tab(k4n::dev::Master* master){
  //---------------------------

  if(ImGui::BeginTabBar("devices_tab##4567")){
    for(int i=0; i< master->list_entity.size(); i++){
      utl::type::Entity* entity = *next(master->list_entity.begin(), i);

      if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
        string name = sensor->icon + "  " + sensor->name;
        if(ImGui::BeginTabItem(name.c_str(), NULL)){
          this->vec_stream_tab(sensor);
          ImGui::EndTabItem();
        }
      }
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
void Stream::vec_stream_tab(k4n::dev::Sensor* sensor){
  if(!sensor->param.data_ready){return;}
  //---------------------------

  //Display capture images
  if(ImGui::BeginTabBar("device_tab##4567")){
    ImVec2 image_size = ImGui::GetContentRegionAvail();

    // Color & Depth & ir
    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("All##4567", NULL)){
      image_size = ImVec2(image_size.x, image_size.y/3-3.33);
      this->draw_camera_color(sensor, image_size);
      this->draw_camera_depth(sensor, image_size);
      this->draw_camera_ir(sensor, image_size);
      ImGui::EndTabItem();
    }

    //Color only
    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Color##4567", NULL)){
      this->draw_camera_color(sensor, image_size);
      ImGui::EndTabItem();
    }

    //Depth only
    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("Depth##4567", NULL)){
      this->draw_camera_depth(sensor, image_size);
      ImGui::EndTabItem();
    }

    //IR only
    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginTabItem("IR##4567", NULL)){
      this->draw_camera_ir(sensor, image_size);
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Device capture windows
void Stream::draw_camera_color(k4n::dev::Sensor* sensor, ImVec2 image_size){
  utl::media::Image* utl_image = &sensor->image.color;
  //---------------------------

  if(utl_image->size == 0) return;
  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[0]->draw_stream(utl_image, image_size);
  this->overlay_capture(sensor, &sensor->color.data, image_size, image_pose);

  //---------------------------
}
void Stream::draw_camera_depth(k4n::dev::Sensor* sensor, ImVec2 image_size){
  utl::media::Image* utl_image = &sensor->image.depth;
  //---------------------------

  if(utl_image->size == 0) return;
  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[1]->draw_stream(utl_image, image_size);
  this->overlay_capture(sensor, &sensor->depth.data, image_size, image_pose);

  //---------------------------
}
void Stream::draw_camera_ir(k4n::dev::Sensor* sensor, ImVec2 image_size){
  utl::media::Image* utl_image = &sensor->image.ir;
  //---------------------------

  if(utl_image->size == 0) return;
  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[2]->draw_stream(utl_image, image_size);
  this->overlay_capture(sensor, &sensor->ir.data, image_size, image_pose);

  //---------------------------
}

//Overlay
void Stream::overlay_capture(k4n::dev::Sensor* sensor, k4n::structure::Data* image, ImVec2 image_size, ImVec2 image_pose){
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

  if(ImGui::Begin(image->name.c_str(), nullptr, flags)){
    this->overlay_information(sensor, image);
    this->overlay_pixel(image, image_size);
  }
  ImGui::End();

  //---------------------------
}
void Stream::overlay_information(k4n::dev::Sensor* sensor, k4n::structure::Data* image){
  //---------------------------

  ImGui::Text("Frame rate: %.0f fps", image->fps);
  ImGui::Text("Timestamp: %.2f s", image->timestamp);
  if(image->temperature != -1){
    ImGui::Text("Temperature: %.2f°", image->temperature);
  }

  //---------------------------
}
void Stream::overlay_pixel(k4n::structure::Data* image, ImVec2 image_size){
  //---------------------------

  if(image->hovered_pixel_x != -1 && image->hovered_pixel_y != -1){
    ImGui::Text("Pixel coord: %.0f %.0f", image->hovered_pixel_x, image->hovered_pixel_y);
    ImGui::Text("Pixel value: %.3f", image->hovered_pixel_m);
  }

  //---------------------------
}
void Stream::compute_hovered_pixel(k4n::structure::Data* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered){
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
    const uint8_t* data = image->buffer;
    size_t index = size_t(image->hovered_pixel_y) * size_t(image->width * 2) + size_t(image->hovered_pixel_x * 2);
    uint16_t pixelData = static_cast<uint16_t>(data[index]) | (static_cast<uint16_t>(data[index + 1]) << 8);
    image->hovered_pixel_m = pixelData / 1000.0f;
  }

  //---------------------------
}

}
