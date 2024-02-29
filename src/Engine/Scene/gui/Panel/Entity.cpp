#include "Entity.h"

#include <Scene/Namespace.h>
#include <Operation/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::scene::gui{

//Constructor / Destructor
Entity::Entity(eng::scene::Node* node_scene, bool* panel_show){
  //---------------------------

  this->sce_database = node_scene->get_scene_database();
  this->ope_location = new ope::attribut::Location();
  this->ope_operation = new ope::Operation();

  this->panel_show = panel_show;
  this->panel_name = "Entity";
  this->item_width = 100;

  //---------------------------
}
Entity::~Entity(){}

//Main function
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
void Entity::entity_title(utl::type::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  this->panel_name = "[Entity]  " + entity->name;

  //---------------------------
}
void Entity::entity_button(utl::type::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Suppression
  if(entity->is_suppressible && ImGui::Button(ICON_FA_TRASH "##4567")){
    utl::type::Set* set_scene = sce_database->get_set_scene();
    set_scene->delete_entity(entity);
    this->close_panel();
    return;
  }

  //Centered
  ImGui::SameLine();
  if(entity->is_movable && ImGui::Button("C##399", ImVec2(20, 0))){
    ope_operation->center_object(entity, entity->get_pose()->min);
  }

  //---------------------------
}
void Entity::entity_parameter(utl::type::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  if(ImGui::BeginTable("entity##table", 2, ImGuiTableFlags_BordersInnerV)){
    this->entity_info(entity);
    this->data_info(entity);
    this->pose_info(entity);

    ImGui::EndTable();
  }

  //---------------------------
}

//Parameter
void Entity::entity_info(utl::type::Entity* entity){
  //---------------------------

  //Type
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Type"); ImGui::TableNextColumn();
  ImGui::Text("%s", entity->entity_type.c_str());

  //Visibility
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Visibility"); ImGui::TableNextColumn();
  bool is_visible = entity->get_visibility();
  if(ImGui::Checkbox("##4555", &is_visible)){
    entity->set_visibility(is_visible);
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
void Entity::data_info(utl::type::Entity* entity){
  utl::type::Data* data = entity->get_data();
  if(data == nullptr) return;
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Format"); ImGui::TableNextColumn();
  static char str_f[256];
  strcpy(str_f, data->file_format.c_str());
  ImGui::SetNextItemWidth(item_width);
  if(ImGui::InputText("##format", str_f, IM_ARRAYSIZE(str_f), ImGuiInputTextFlags_EnterReturnsTrue)){
    data->file_format = str_f;
  }

  //Uniform collection color
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Color"); ImGui::TableNextColumn();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs;
  flags |= ImGuiColorEditFlags_AlphaBar;
  if(ImGui::ColorEdit4("Color", (float*)&data->unicolor, flags)){
    ope_location->set_unicolor(entity);
  }

  //Primitive size
  switch(data->draw_type){
    case utl::topology::POINT:{
      this->primitive_point(data);
      break;
    }
    case utl::topology::LINE:{
      this->primitive_line(data);
      break;
    }
  }

  //---------------------------
}
void Entity::pose_info(utl::type::Entity* entity){
  utl::type::Pose* pose = entity->get_pose();
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
    ope_operation->make_translation_from_root(entity, vec3(0, 0, 0));
  }

  //---------------------------
}

//Primitive
void Entity::primitive_line(utl::type::Data* data){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Line width
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Line width"); ImGui::TableNextColumn();
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    data->line.width--;

    if(data->line.width <= 1){
      data->line.width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    data->line.width++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", data->line.width);

  //---------------------------
}
void Entity::primitive_point(utl::type::Data* data){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Number of points
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Point No"); ImGui::TableNextColumn();
  string nb_point = math::thousand_separator(data->point.size);
  ImGui::Text("%s", nb_point.c_str());

  //Point size
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Point size"); ImGui::TableNextColumn();
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    data->point.width--;

    if(data->point.width <= 1){
      data->point.width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    data->point.width++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", data->point.width);

  //---------------------------
}

}
