#include "Stream.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Vulkan/Namespace.h>
#include <GUI/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::gui{

//Constructor / Destructor
Stream::Stream(dyn::Node* node_dynamic, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->node_engine = node_dynamic->get_node_engine();
  this->dat_graph = node_data->get_data_graph();
  this->dat_set = node_data->get_data_set();

  this->show_window = show_window;
  this->name = "Stream";

  //---------------------------
  this->init();
}
Stream::~Stream(){}

//Main function
void Stream::init(){
  //---------------------------

  for(int i=0; i<10; i++){
    gui_media::Stream* stream = new gui_media::Stream(node_engine);
    this->vec_stream.push_back(stream);
  }

  //---------------------------
}
void Stream::run_panel(){
  utl::type::Element* element = dat_graph->get_selected_element();
  //---------------------------

  //Chekc if it contain entities
  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    if(set->list_entity.size() == 0) return;
    else if(set->active_entity->list_image.size() == 0) return;
  }

  if(*show_window && element != nullptr){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(100, 400), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(element);

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Stream::design_panel(utl::type::Element* element){
  //---------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    this->draw_set_tabbar(set);
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    this->draw_stream_tabbar(entity);
  }

  //---------------------------
}

//All devices
void Stream::draw_set_tabbar(dat::base::Set* set){
  //---------------------------

  if(ImGui::BeginTabBar("devices_tab##4567")){
    for(int i=0; i<set->list_entity.size(); i++){
      dat::base::Entity* entity = *next(set->list_entity.begin(), i);

      string name = entity->icon + "  " + entity->name;
      if(ImGui::BeginTabItem(name.c_str(), NULL)){
        this->draw_stream_tabbar(entity);
        ImGui::EndTabItem();
      }
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
void Stream::draw_stream_tabbar(dat::base::Entity* entity){
  list<utl::media::Image*> list_image = entity->list_image;
  //---------------------------

  //Display capture images
  if(ImGui::BeginTabBar("device_tab##4567")){
    ImVec2 size = ImGui::GetContentRegionAvail();

    //All in one
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("All##4567", NULL)){
      size = ImVec2(size.x, size.y / list_image.size() - 3.33);

      for(int i=0; i<list_image.size(); i++){
        utl::media::Image* image = *next(list_image.begin(), i);
        this->draw_stream_image(image, size);
      }

      ImGui::EndTabItem();
    }

    //All image in separate tab
    for(int i=0; i<list_image.size(); i++){
      utl::media::Image* image = *next(list_image.begin(), i);

      ImGui::SetNextItemWidth(100);
      string title = image->name + "##4567";
      if(ImGui::BeginTabItem(title.c_str(), NULL)){
        this->draw_stream_image(image, size);
        ImGui::EndTabItem();
      }
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}
void Stream::draw_stream_image(utl::media::Image* image, ImVec2 size){
  //---------------------------

  if(image->size == 0) return;
  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_stream[0]->draw_stream(image, size);
  //this->overlay_capture(entity, &entity->color.data, size, image_pose);

  //---------------------------
}

//Overlay
void Stream::overlay_capture(dat::base::Entity* entity, utl::media::Image* image, ImVec2 size, ImVec2 image_pose){
  //---------------------------
/*
  //Hovered pixel
  bool image_hovered = ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenOverlappedByWindow);
  this->compute_hovered_pixel(image, size, image_pose, image_hovered);

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
    this->overlay_information(entity, image);
    this->overlay_pixel(image, size);
  }
  ImGui::End();
*/
  //---------------------------
}
void Stream::overlay_information(dat::base::Entity* entity, utl::media::Image* image){
  //---------------------------
/*
  ImGui::Text("Frame rate: %.0f fps", image->fps);
  ImGui::Text("Timestamp: %.2f s", image->timestamp);
  if(image->temperature != -1){
    ImGui::Text("Temperature: %.2f°", image->temperature);
  }
*/
  //---------------------------
}
void Stream::overlay_pixel(utl::media::Image* image, ImVec2 size){
  //---------------------------
/*
  if(image->hovered_pixel_x != -1 && image->hovered_pixel_y != -1){
    ImGui::Text("Pixel coord: %.0f %.0f", image->hovered_pixel_x, image->hovered_pixel_y);
    ImGui::Text("Pixel value: %.3f", image->hovered_pixel_m);
  }
*/
  //---------------------------
}
void Stream::compute_hovered_pixel(utl::media::Image* image, ImVec2 size, ImVec2 image_pose, bool image_hovered){
  //---------------------------
/*
  //Reinitialize coord values
  image->hovered_pixel_x = -1;
  image->hovered_pixel_y = -1;

  // Compute hovered pixel coordinates
  if(image_hovered && (image->name == "depth" || image->name == "ir")){
    ImVec2 mousePos = ImGui::GetIO().MousePos;
    ImVec2 hoveredUIPixel;
    ImVec2 sourceImageDimensions = ImVec2(image->width, image->height);
    hoveredUIPixel.x = mousePos.x - image_pose.x;
    hoveredUIPixel.x = std::min(hoveredUIPixel.x, size.x);
    hoveredUIPixel.x = std::max(hoveredUIPixel.x, 0.0f);

    hoveredUIPixel.y = mousePos.y - image_pose.y;
    hoveredUIPixel.y = std::min(hoveredUIPixel.y, size.y);
    hoveredUIPixel.y = std::max(hoveredUIPixel.y, 0.0f);

    const float uiCoordinateToImageCoordinateRatio = sourceImageDimensions.x / size.x;

    image->hovered_pixel_x = hoveredUIPixel.x * uiCoordinateToImageCoordinateRatio;
    image->hovered_pixel_y = hoveredUIPixel.y * uiCoordinateToImageCoordinateRatio;

    //Pixel value
    const uint8_t* data = image->buffer;
    size_t index = size_t(image->hovered_pixel_y) * size_t(image->width * 2) + size_t(image->hovered_pixel_x * 2);
    uint16_t pixelData = static_cast<uint16_t>(data[index]) | (static_cast<uint16_t>(data[index + 1]) << 8);
    image->hovered_pixel_m = pixelData / 1000.0f;
  }
*/
  //---------------------------
}

}
