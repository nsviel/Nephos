#include "Stream.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Vulkan/Namespace.h>
#include <GUI/Namespace.h>
#include <Data/Namespace.h>
#include <Render/Namespace.h>


namespace dyn::gui{

//Constructor / Destructor
Stream::Stream(dyn::Node* node_dynamic, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->node_engine = node_dynamic->get_node_engine();
  this->dat_graph = node_data->get_dat_graph();
  this->dat_set = node_data->get_data_set();
  this->gui_overlay = new dyn::gui::Overlay();

  for(int i=0; i<10; i++){
    rnd::Stream* stream = new rnd::Stream(node_engine);
    this->vec_stream.push_back(stream);
  }

  this->show_window = show_window;
  this->name = "Stream";

  //---------------------------
}
Stream::~Stream(){}

//Main function
void Stream::run_panel(){
  dat::base::Set* set = dat_graph->get_selected_set();
  //---------------------------

  if(*show_window && set->list_entity.size() != 0){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(100, 400), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(set);

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Stream::design_panel(dat::base::Set* set){
  //---------------------------

  this->draw_set_tabbar(set);

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
  //gui_overlay->overlay_capture(entity, &entity->color.data, size, image_pose);

  //---------------------------
}

}
