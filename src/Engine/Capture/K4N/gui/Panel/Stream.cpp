#include "Stream.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


namespace eng::k4n::gui{

//Constructor / Destructor
Stream::Stream(eng::k4n::Node* node_k4n, bool* show_window){
  //---------------------------

  eng::Node* engine = node_k4n->get_node_engine();

  this->node_k4n = node_k4n;
  this->k4n_swarm = node_k4n->get_k4n_swarm();

  this->vec_gui_stream.push_back(new eng::render::gui::Stream(engine));
  this->vec_gui_stream.push_back(new eng::render::gui::Stream(engine));
  this->vec_gui_stream.push_back(new eng::render::gui::Stream(engine));
  this->vec_gui_stream.push_back(new eng::render::gui::Stream(engine));

  this->show_window = show_window;
  this->name = "Stream";

  //---------------------------
}
Stream::~Stream(){}

//Main function
void Stream::run_panel(){
  eng::k4n::dev::Master* master = k4n_swarm->get_selected_master();
  //---------------------------

  if(*show_window && master != nullptr && master->nb_entity != 0){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(master);

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Stream::design_panel(eng::k4n::dev::Master* master){
  //---------------------------

  this->vec_device_tab(master);

  //---------------------------
}

//All devices
void Stream::vec_device_tab(eng::k4n::dev::Master* master){
  //---------------------------

  if(ImGui::BeginTabBar("devices_tab##4567")){
    for(int i=0; i< master->list_entity.size(); i++){
      utl::type::Entity* entity = *next(master->list_entity.begin(), i);

      if(eng::k4n::dev::Sensor* sensor = dynamic_cast<eng::k4n::dev::Sensor*>(entity)){
        //Force tab open if another sensor selected
        ImGuiTabItemFlags flag = get_device_tab_flag(sensor);
        string name = sensor->icon + "  " + sensor->name;
        if(ImGui::BeginTabItem(name.c_str(), NULL, flag)){
          master->set_selected_entity(sensor);
          this->vec_stream_tab(sensor);
          ImGui::EndTabItem();
        }
      }
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
void Stream::vec_stream_tab(eng::k4n::dev::Sensor* sensor){
  if(!sensor->param.data_ready){return;}
  //---------------------------

  //Display capture images
  if(ImGui::BeginTabBar("device_tab##4567")){
    ImVec2 image_size = ImGui::GetContentRegionAvail();
    ImGuiTabItemFlags flag;

    ImGui::SetNextItemWidth(100);
    flag = get_sensor_tab_flag(0);
    if (ImGui::BeginTabItem("All##4567", NULL)){
      image_size = ImVec2(image_size.x, image_size.y/3-3.33);
      this->draw_camera_color(sensor, image_size);
      this->draw_camera_depth(sensor, image_size);
      this->draw_camera_ir(sensor, image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    flag = get_sensor_tab_flag(1);
    if (ImGui::BeginTabItem("Color##4567", NULL)){
      this->draw_camera_color(sensor, image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    flag = get_sensor_tab_flag(2);
    if(sensor->color.data_to_depth.k4a_image.is_valid() && ImGui::BeginTabItem("Color from depth##4567", NULL)){
      this->draw_camera_color_from_depth(sensor, image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    flag = get_sensor_tab_flag(3);
    if (ImGui::BeginTabItem("Depth##4567", NULL)){
      this->draw_camera_depth(sensor, image_size);
      ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);
    flag = get_sensor_tab_flag(4);
    if (ImGui::BeginTabItem("IR##4567", NULL)){
      this->draw_camera_ir(sensor, image_size);
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Device capture windows
void Stream::draw_camera_color(eng::k4n::dev::Sensor* sensor, ImVec2 image_size){
  eng::k4n::structure::Data* data = &sensor->color.data;
  //---------------------------

  utl::media::Image utl_image;
  utl_image.data_vec = data->utl_image.data_vec;
  utl_image.size = data->utl_image.size;
  utl_image.width = data->width;
  utl_image.height = data->height;
  utl_image.format = data->format;

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[0]->draw_stream(&utl_image, image_size);
  this->overlay_capture(sensor, data, image_size, image_pose);

  //---------------------------
}
void Stream::draw_camera_color_from_depth(eng::k4n::dev::Sensor* sensor, ImVec2 image_size){
  eng::k4n::structure::Data* data = &sensor->color.data_to_depth;
  //---------------------------

  utl::media::Image utl_image;
  utl_image.data_raw = data->buffer_raw;
  utl_image.size = data->size;
  utl_image.width = data->width;
  utl_image.height = data->height;
  utl_image.format = data->format;

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[3]->draw_stream(&utl_image, image_size);
  this->overlay_capture(sensor, data, image_size, image_pose);

  //---------------------------
}
void Stream::draw_camera_depth(eng::k4n::dev::Sensor* sensor, ImVec2 image_size){
  eng::k4n::structure::Data* data = &sensor->depth.data;
  //---------------------------

  utl::media::Image utl_image;
  utl_image.data_vec = data->utl_image.data_vec;
  utl_image.size = data->utl_image.size;
  utl_image.width = data->width;
  utl_image.height = data->height;
  utl_image.format = "R8G8B8A8_SRGB";

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[1]->draw_stream(&utl_image, image_size);
  this->overlay_capture(sensor, data, image_size, image_pose);

  //---------------------------
}
void Stream::draw_camera_ir(eng::k4n::dev::Sensor* sensor, ImVec2 image_size){
  eng::k4n::structure::Data* data = &sensor->ir.data;
  //---------------------------

  utl::media::Image utl_image;
  utl_image.data_vec = data->utl_image.data_vec;
  utl_image.size = data->utl_image.size;
  utl_image.width = data->width;
  utl_image.height = data->height;
  utl_image.format = "B8G8R8A8_SRGB";

  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_gui_stream[2]->draw_stream(&utl_image, image_size);
  this->overlay_capture(sensor, data, image_size, image_pose);

  //---------------------------
}

//Overlay
void Stream::overlay_capture(eng::k4n::dev::Sensor* sensor, eng::k4n::structure::Data* image, ImVec2 image_size, ImVec2 image_pose){
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
    this->overlay_information(sensor, image);
    this->overlay_pixel(image, image_size);
  }
  ImGui::End();

  //---------------------------
}
void Stream::overlay_information(eng::k4n::dev::Sensor* sensor, eng::k4n::structure::Data* image){
  //---------------------------

  ImGui::Text("Frame rate: %.2f fps", sensor->param.fps.current);
  ImGui::Text("Timestamp: %.2f s", image->timestamp);
  if(image->temperature != -1){
    ImGui::Text("Temperature: %.2f°", image->temperature);
  }

  //---------------------------
}
void Stream::overlay_pixel(eng::k4n::structure::Data* image, ImVec2 image_size){
  //---------------------------

  if(image->hovered_pixel_x != -1 && image->hovered_pixel_y != -1){
    ImGui::Text("Pixel coord: %.0f %.0f", image->hovered_pixel_x, image->hovered_pixel_y);
    ImGui::Text("Pixel value: %.3f", image->hovered_pixel_m);
  }

  //---------------------------
}
void Stream::compute_hovered_pixel(eng::k4n::structure::Data* image, ImVec2 image_size, ImVec2 image_pose, bool image_hovered){
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
    const std::vector<uint8_t>& data = image->buffer_vec;
    size_t index = size_t(image->hovered_pixel_y) * size_t(image->width * 2) + size_t(image->hovered_pixel_x * 2);
    uint16_t pixelData = static_cast<uint16_t>(data[index]) | (static_cast<uint16_t>(data[index + 1]) << 8);
    image->hovered_pixel_m = pixelData / 1000.0f;
  }

  //---------------------------
}

//Subfunction
ImGuiTabItemFlags Stream::get_device_tab_flag(eng::k4n::dev::Sensor* sensor){
  eng::k4n::dev::Master* master = sensor->master;
  //---------------------------

  ImGuiTabItemFlags flag = 0;
  /*static int UID = master->selected_entity->UID;
  if(master->is_selected_entity(sensor) && sensor->UID != UID){
    flag = ImGuiTabItemFlags_SetSelected;
    UID = master->selected_entity->UID;
    current_tab_id = 0;
  }*/

  //---------------------------
  return flag;
}
ImGuiTabItemFlags Stream::get_sensor_tab_flag(int tab_id){
  //---------------------------

  ImGuiTabItemFlags flag = 0;
  /*static int UID = current_tab_id;
  if(current_tab_id == tab_id && tab_id != UID){
    flag = ImGuiTabItemFlags_SetSelected;
    UID = tab_id;
  }*/

  //---------------------------
  return flag;
}

}
