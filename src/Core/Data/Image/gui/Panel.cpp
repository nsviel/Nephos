#include "Panel.h"

#include <Data/Image/Namespace.h>
#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Engine/Renderer/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>


namespace dat::img::gui{

//Constructor / Destructor
Panel::Panel(dat::img::Node* node_image, bool* show_window){
  //---------------------------

  dat::gph::Node* node_graph = node_image->get_node_graph();
  dat::elm::Node* node_element = node_image->get_node_element();
  vk::Node* node_vulkan = node_image->get_node_vulkan();

  this->gph_selection = node_graph->get_gph_selection();
  this->dat_set = node_element->get_dat_set();
  this->gui_overlay = new dat::img::gui::Overlay();

  for(int i=0; i<20; i++){
    dat::img::gui::Stream* stream = new dat::img::gui::Stream(node_image);
    this->vec_stream.push_back(stream);
  }

  this->show_window = show_window;
  this->name = "Stream";

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  std::shared_ptr<dat::base::Entity> entity = gph_selection->get_selected_entity();
  if(!entity) return;
  //---------------------------

  if(*show_window && !entity->data->map_image.empty()){
    ImGuiWindowFlags flag;
    flag |= ImGuiWindowFlags_NoCollapse;
    flag |= ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(100, 400), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, flag) == 1){

      this->design_panel(entity);

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(std::shared_ptr<dat::base::Entity> entity){
  //---------------------------

  this->draw_stream_tabbar(entity);

  //---------------------------
}

//All devices
void Panel::draw_stream_tabbar(std::shared_ptr<dat::base::Entity> entity){
  utl::base::Data& data = *entity->data;
  //---------------------------

  //Get vector of display image
  std::vector<std::shared_ptr<utl::media::Image>> vec_image;
  for(auto& [name, image] : data.map_image){
    if(image->display){
      vec_image.push_back(image);
    }
  }

  //Display capture images
  if(ImGui::BeginTabBar("device_tab##4567")){
    ImVec2 dimension = ImGui::GetContentRegionAvail();

    //All in one
    ImGui::SetNextItemWidth(100);
    if(ImGui::BeginTabItem("All##4567", NULL)){
      dimension.y = dimension.y / vec_image.size() - 3.33;

      int index = 0;
      for(auto& image : vec_image){
        this->draw_stream_image(image, dimension, index++);
      }

      ImGui::EndTabItem();
    }

    //All image in separate tab
    int index = 0;
    for(auto& image : vec_image){
      std::string title = image->name + "##4567";
      ImGui::SetNextItemWidth(100);
      if(ImGui::BeginTabItem(title.c_str(), NULL)){
        this->draw_stream_image(image, dimension, index++);
        ImGui::EndTabItem();
      }
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}
void Panel::draw_stream_image(std::shared_ptr<utl::media::Image> image, ImVec2 dimension, int idx){
  if(idx >= vec_stream.size()) return;
  //---------------------------

  if(image->size == 0) return;
  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_stream[idx]->draw_stream(image, dimension);
  //gui_overlay->overlay_capture(entity, &entity->color.data, dimension, image_pose);

  //---------------------------
}

}
