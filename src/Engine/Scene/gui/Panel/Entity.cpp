#include "Entity.h"

#include <Engine/Scene/Namespace.h>
#include <Engine/Operation/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::scene::gui{

//Constructor / Destructor
Entity::Entity(eng::scene::Node* sce_node, bool* panel_show){
  //---------------------------

  this->sce_scene = sce_node->get_scene();
  this->ope_attribut = new eng::ope::Attribut();
  this->ope_operation = new eng::ope::Operation();

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
    sce_scene->delete_scene_entity(entity);
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
    this->general_info(entity);

    //Data info
    utl::type::Data* data = entity->get_data();
    utl::type::Pose* pose = entity->get_pose();
    if(data != nullptr){
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
        ope_attribut->set_unicolor(entity);
      }

      //Root pos
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      vec3& root = pose->root;
      ImGui::Text("Root"); ImGui::TableNextColumn();
      ImGui::NextColumn();
      ImGui::Text("%.2f  %.2f  %.2f", root.x, root.y, root.z);
      ImGui::SameLine();
      if(ImGui::Button("R", ImVec2(15,0))){
        root = vec3(0,0,0);
      }

      //Primitive size
      if(data->draw_type_name == "point"){
        this->data_point(data);
      }
      else if(data->draw_type_name == "line"){
        this->data_line(data);
      }
    }

    ImGui::EndTable();
  }

  //---------------------------
}

//Parameter
void Entity::general_info(utl::type::Entity* entity){
  //---------------------------

  //Type
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Type"); ImGui::TableNextColumn();
  ImGui::Text("%s", entity->type.c_str());

  //Visibility
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Visibility"); ImGui::TableNextColumn();
  bool is_visible = entity->get_visibility();
  if(ImGui::Checkbox("##4555", &is_visible)){
    entity->visibility_entity(is_visible);
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
void Entity::data_line(utl::type::Data* data){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Line width
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Line width"); ImGui::TableNextColumn();
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    data->draw_line_width--;

    if(data->draw_line_width <= 1){
      data->draw_line_width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    data->draw_line_width++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", data->draw_line_width);

  //---------------------------
}
void Entity::data_point(utl::type::Data* data){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Number of points
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Point No"); ImGui::TableNextColumn();
  string nb_point = math::thousand_separator(data->nb_point);
  ImGui::Text("%s", nb_point.c_str());

  //Point size
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Point size"); ImGui::TableNextColumn();
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    data->draw_point_size--;

    if(data->draw_point_size <= 1){
      data->draw_point_size = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    data->draw_point_size++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", data->draw_point_size);

  //---------------------------
}

}
