#include "Panel.h"

#include <Data/Element/Namespace.h>
#include <Data/Attribut/Namespace.h>
#include <Engine/Transformation/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>
#include <imgui/core/imgui.h>


namespace dat::entity::gui{

//Constructor / Destructor
Panel::Panel(dat::elm::Node* node_element){
  //---------------------------

  this->gui_topology = new dat::entity::gui::Topology();
  this->gui_data = new dat::entity::gui::Data(node_element);
  this->trf_operation = new eng::trf::Operation();

  this->panel_show = false;
  this->panel_name = "Entity";
  this->item_width = 100;

  //---------------------------
}
Panel::~Panel(){}

//Main functionf
void Panel::run_panel(){
  //---------------------------

  if(panel_show){
    ImGuiWindowFlags flag;
    flag |= ImGuiWindowFlags_NoCollapse;
    flag |= ImGuiWindowFlags_AlwaysAutoResize;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2, 0.2, 0.2, 1));
    if(ImGui::Begin(panel_name.c_str(), &panel_show, flag) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  if(entity.expired()) close_panel();
  //---------------------------

  auto entity_ptr = entity.lock();
  this->entity_title(entity_ptr);
  this->entity_button(entity_ptr);
  this->entity_parameter(entity_ptr);

  //---------------------------
}
void Panel::close_panel(){
  //---------------------------

  this->entity.reset();
  this->panel_show = false;

  //---------------------------
}

//Subfunction
void Panel::entity_title(std::shared_ptr<dat::base::Entity> entity){
  if(!entity) return;
  //---------------------------

  this->panel_name = "[Entity]  " + entity->name;

  //---------------------------
}
void Panel::entity_button(std::shared_ptr<dat::base::Entity> entity){
  if(!entity) return;
  //---------------------------

  utl::base::Pose& pose = *entity->pose;

  //Centered
  if(pose.is_movable && ImGui::Button("C##399", ImVec2(20, 0))){
    trf_operation->center_object(entity, pose.min);
  }

  //Attribut
  if(ImGui::Button("A##399", ImVec2(20, 0))){
    trf_operation->center_object(entity, pose.min);
  }

  //---------------------------
}
void Panel::entity_parameter(std::shared_ptr<dat::base::Entity> entity){
  if(!entity) return;
  //---------------------------

  ImGui::BeginTable("entity##table", 2, ImGuiTableFlags_BordersInnerV);

  gui_data->draw_entity_data(entity);
  gui_topology->entity_typology(entity);

  ImGui::EndTable();

  //---------------------------
}

}
