#include "Panel.h"

#include <Data/Namespace.h>
#include <Operation/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>
#include <imgui/core/imgui.h>


namespace dat::gui::entity{

//Constructor / Destructor
Panel::Panel(dat::Node* node_data, bool* panel_show){
  //---------------------------

  this->dat_selection = node_data->get_dat_selection();
  this->dat_set = node_data->get_dat_set();
  this->gui_topology = new dat::gui::entity::Topology();
  this->gui_data = new dat::gui::entity::Data(node_data);
  this->ope_location = new ope::attribut::Location();
  this->ope_operation = new ope::Operation();

  this->panel_show = panel_show;
  this->panel_name = "Entity";
  this->item_width = 100;

  //---------------------------
}
Panel::~Panel(){}

//Main functionf
void Panel::run_panel(){
  //---------------------------

  if(*panel_show){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2, 0.2, 0.2, 1));
    if(ImGui::Begin(panel_name.c_str(), panel_show, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  if(entity == nullptr) close_panel();
  //---------------------------

  this->entity_title(entity);
  this->entity_button(entity);
  this->entity_parameter(entity);

  //---------------------------
}
void Panel::close_panel(){
  //---------------------------

  this->entity = nullptr;
  *panel_show = false;

  //---------------------------
}

//Subfunction
void Panel::entity_title(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  this->panel_name = "[Entity]  " + entity->name;

  //---------------------------
}
void Panel::entity_button(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Suppression
  if(entity->is_suppressible && ImGui::Button(ICON_FA_TRASH "##4567")){
    dat::base::Set* set = dat_selection->get_selected_set();
    dat_set->remove_entity(set, entity);
    this->close_panel();
    return;
  }

  //Centered
  ImGui::SameLine();
  if(entity->pose.movable && ImGui::Button("C##399", ImVec2(20, 0))){
    utl::base::Pose* pose = &entity->pose;;
    ope_operation->center_object(entity, pose->min);
  }

  //---------------------------
}
void Panel::entity_parameter(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  ImGui::BeginTable("entity##table", 2, ImGuiTableFlags_BordersInnerV);

  gui_data->draw_entity_data(entity);
  gui_topology->entity_typology(entity);

  ImGui::EndTable();

  //---------------------------
}

}
