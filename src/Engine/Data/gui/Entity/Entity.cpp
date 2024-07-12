#include "Entity.h"

#include <Data/Namespace.h>
#include <Operation/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>
#include <imgui/core/imgui.h>


namespace dat::gui{

//Constructor / Destructor
Entity::Entity(dat::Node* node_data, bool* panel_show){
  //---------------------------

  this->dat_selection = node_data->get_dat_selection();
  this->dat_set = node_data->get_dat_set();
  this->dat_entity = node_data->get_dat_entity();
  this->ope_location = new ope::attribut::Location();
  this->ope_operation = new ope::Operation();

  this->panel_show = panel_show;
  this->panel_name = "Entity";
  this->item_width = 100;

  //---------------------------
}
Entity::~Entity(){}

//Main functionf
void Entity::run_panel(){
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
void Entity::design_panel(){
  if(entity == nullptr) close_panel();
  //---------------------------

  this->entity_title(entity);
  this->entity_button(entity);
  this->entity_parameter(entity);

  //---------------------------
}
void Entity::close_panel(){
  //---------------------------

  this->entity = nullptr;
  *panel_show = false;

  //---------------------------
}

//Subfunction
void Entity::entity_title(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  this->panel_name = "[Entity]  " + entity->name;

  //---------------------------
}
void Entity::entity_button(dat::base::Entity* entity){
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
void Entity::entity_parameter(dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  ImGui::BeginTable("entity##table", 2, ImGuiTableFlags_BordersInnerV);

  this->entity_info(entity);
  this->entity_data(entity);
  this->entity_typology(entity);
  this->entity_pose(entity);

  ImGui::EndTable();

  //---------------------------
}

//Parameter
void Entity::entity_info(dat::base::Entity* entity){
  //---------------------------

  //Visibility
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Visibility"); ImGui::TableNextColumn();
  utl::base::Data* data = &entity->data;
  if(ImGui::Checkbox("##4555", &data->is_visible)){
    dat_entity->visibility_entity(entity, data->is_visible);
  }

  //Name
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Name"); ImGui::TableNextColumn();
  static char str_n[256];
  strcpy(str_n, entity->name.c_str());
  ImGui::SetNextItemWidth(item_width);
  if(ImGui::InputText("##name", str_n, IM_ARRAYSIZE(str_n), ImGuiInputTextFlags_EnterReturnsTrue)){
    entity->name = str_n;
  }

  //---------------------------
}
void Entity::entity_data(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  if(data == nullptr) return;
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Format"); ImGui::TableNextColumn();
  static char str_f[256];
  strcpy(str_f, data->path.format.c_str());
  ImGui::SetNextItemWidth(item_width);
  if(ImGui::InputText("##format", str_f, IM_ARRAYSIZE(str_f), ImGuiInputTextFlags_EnterReturnsTrue)){
    data->path.format = str_f;
  }

  //Uniform collection color
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Color"); ImGui::TableNextColumn();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs;
  flags |= ImGuiColorEditFlags_AlphaBar;
  if(ImGui::ColorEdit4("Color", (float*)&data->unicolor, flags)){
    ope_location->set_unicolor(entity);
  }

  //---------------------------
  ImGui::Separator();
}
void Entity::entity_pose(dat::base::Entity* entity){
  utl::base::Pose* pose = &entity->pose;;
  if(pose == nullptr) return;
  //---------------------------

  //Root pos
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Root"); ImGui::TableNextColumn();
  ImGui::NextColumn();
  float floatArray[3];
  std::memcpy(floatArray, &pose->root, sizeof(float) * 3);
  if(ImGui::DragFloat3("##434", floatArray, 0.01f, -100.0f, 100.0f, "%.2f")){
    glm::vec3 new_root(floatArray[0], floatArray[1], floatArray[2]);
    ope_operation->make_translation_from_root(entity, new_root);
  }
  ImGui::SameLine();
  if(ImGui::Button("R", ImVec2(15,0))){
    ope_operation->make_translation_from_root(entity, glm::vec3(0, 0, 0));
  }

  //---------------------------
}

//Primitive
void Entity::entity_typology(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  if(data == nullptr) return;
  //---------------------------

  //Primitive size
  switch(data->topology.type){
    case utl::topology::POINT:{
      this->topology_point(data);
      break;
    }
    case utl::topology::LINE:{
      this->topology_line(data);
      break;
    }
    case utl::topology::TRIANGLE:{
      this->topology_triangle(data);
      break;
    }
  }

  //---------------------------
}
void Entity::topology_line(utl::base::Data* data){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Draw type
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Topology"); ImGui::TableNextColumn();
  ImGui::Text("line");

  //Number of points
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Count"); ImGui::TableNextColumn();
  std::string nb_point = math::thousand_separator(data->size / 2);
  ImGui::Text("%s", nb_point.c_str());

  //Line width
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Line width"); ImGui::TableNextColumn();
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    data->topology.width--;

    if(data->topology.width <= 1){
      data->topology.width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    data->topology.width++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", data->topology.width);

  //---------------------------
}
void Entity::topology_point(utl::base::Data* data){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Draw type
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Topology"); ImGui::TableNextColumn();
  ImGui::Text("point");

  //Number of points
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Count"); ImGui::TableNextColumn();
  std::string nb_point = math::thousand_separator(data->size);
  ImGui::Text("%s", nb_point.c_str());

  //Point size
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Size"); ImGui::TableNextColumn();
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    data->topology.width--;

    if(data->topology.width <= 1){
      data->topology.width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    data->topology.width++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", data->topology.width);

  //---------------------------
}
void Entity::topology_triangle(utl::base::Data* data){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Draw type
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Topology"); ImGui::TableNextColumn();
  ImGui::Text("triangle");

  //Number of points
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Count"); ImGui::TableNextColumn();
  std::string nb_point = math::thousand_separator(data->size / 3);
  ImGui::Text("%s", nb_point.c_str());

  //---------------------------
}

}
