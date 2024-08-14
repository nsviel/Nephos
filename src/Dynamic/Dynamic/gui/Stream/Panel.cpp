#include "Panel.h"

#include <Core/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Element/Namespace.h>
#include <Data/Namespace.h>
#include <Renderer/Namespace.h>


namespace dyn::gui::stream{

//Constructor / Destructor
Panel::Panel(dyn::Node* node_dynamic, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();
  dat::graph::Node* node_graph = node_data->get_node_graph();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->node_engine = node_dynamic->get_node_engine();
  this->dat_selection = node_graph->get_dat_selection();
  this->dat_set = node_element->get_dat_set();
  this->gui_overlay = new dyn::gui::stream::Overlay();

  for(int i=0; i<20; i++){
    rnd::gui::Stream* stream = new rnd::gui::Stream(node_engine);
    this->vec_stream.push_back(stream);
  }

  this->show_window = show_window;
  this->name = "Stream";

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  if(entity == nullptr) return;
  //---------------------------

  if(*show_window && entity->list_image.size() != 0){
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
void Panel::design_panel(dat::base::Entity* entity){
  //---------------------------

  this->draw_stream_tabbar(entity);

  //---------------------------
}

//All devices
void Panel::draw_stream_tabbar(dat::base::Entity* entity){
  std::list<utl::media::Image*> list_image = entity->list_image;
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
        this->draw_stream_image(image, size, i);
      }

      ImGui::EndTabItem();
    }

    //All image in separate tab
    for(int i=0; i<list_image.size(); i++){
      utl::media::Image* image = *next(list_image.begin(), i);

      ImGui::SetNextItemWidth(100);
      std::string title = image->name + "##4567";
      if(ImGui::BeginTabItem(title.c_str(), NULL)){
        this->draw_stream_image(image, size, i);
        ImGui::EndTabItem();
      }
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}
void Panel::draw_stream_image(utl::media::Image* image, ImVec2 size, int idx){
  if(idx >= vec_stream.size()) return;
  //---------------------------

  if(image->size == 0) return;
  ImVec2 image_pose = ImGui::GetCursorScreenPos();
  vec_stream[idx]->draw_stream(image, size);
  //gui_overlay->overlay_capture(entity, &entity->color.data, size, image_pose);

  //---------------------------
}

}
