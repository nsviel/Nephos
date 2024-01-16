#include "Entity.h"

#include <GUI.h>
#include <Engine/Engine.h>
#include <image/IconsFontAwesome6.h>


namespace gui::rnd::data{

//Constructor / Destructor
Entity::Entity(GUI* gui, bool* panel_show){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::scene::Node* node_scene = engine->get_node_scene();

  this->sce_scene = node_scene->get_scene();
  this->sce_operation = node_scene->get_scene_operation();
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
void Entity::entity_title(entity::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  this->panel_name = "[Entity]  " + entity->name;

  //---------------------------
}
void Entity::entity_button(entity::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Suppression
  if(entity->is_suppressible && ImGui::Button(ICON_FA_TRASH "##4567")){
    sce_scene->delete_entity(entity);
    this->close_panel();
    return;
  }

  //Centered
  ImGui::SameLine();
  if(entity->is_movable && ImGui::Button("C##399", ImVec2(20, 0))){
    sce_operation->make_center(entity);
  }

  //---------------------------
}
void Entity::entity_parameter(entity::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  if(ImGui::BeginTable("entity##table", 2, ImGuiTableFlags_BordersInnerV)){
    //Type
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Type"); ImGui::TableNextColumn();
    ImGui::Text("%s", entity->type.c_str());

    //Visibility
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Visibility"); ImGui::TableNextColumn();
    if(ImGui::Checkbox("##4555", &entity->is_visible)){
      entity->visibility_entity(entity->is_visible);
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

    //Format


    //FOUTRE TOUT CE BORDER DE TYPE ENTITY DANS scene/OPERATION
    if(k4n::Device* device = dynamic_cast<k4n::Device*>(entity)){
      entity = device->cloud.object;
    }

    if(entity::Object* object = dynamic_cast<entity::Object*>(entity)){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Format"); ImGui::TableNextColumn();
      static char str_f[256];
      strcpy(str_f, object->data->file_format.c_str());
      ImGui::SetNextItemWidth(item_width);
      if(ImGui::InputText("##format", str_f, IM_ARRAYSIZE(str_f), ImGuiInputTextFlags_EnterReturnsTrue)){
        object->data->file_format = str_f;
      }

      //Uniform collection color
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Color"); ImGui::TableNextColumn();
      ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs;
      flags |= ImGuiColorEditFlags_AlphaBar;
      if(ImGui::ColorEdit4("Color", (float*)&object->data->unicolor, flags)){
        ope_attribut->set_unicolor(object);
        sce_scene->update_object(object);
      }

      //Root pos
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      vec3& root = object->data->root;
      ImGui::Text("Root"); ImGui::TableNextColumn();
      ImGui::NextColumn();
      ImGui::Text("%.2f  %.2f  %.2f", root.x, root.y, root.z);
      ImGui::SameLine();
      if(ImGui::Button("R", ImVec2(15,0))){
        root = vec3(0,0,0);
      }

      //Primitive size
      if(object->data->draw_type_name == "point"){
        this->entity_point(object);
      }
      else if(object->data->draw_type_name == "line"){
        this->entity_line(object);
      }
    }

    ImGui::EndTable();
  }

  //---------------------------
}

//Primitive size
void Entity::entity_line(entity::Object* object){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Line width
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Line width"); ImGui::TableNextColumn();
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    object->data->draw_line_width--;

    if(object->data->draw_line_width <= 1){
      object->data->draw_line_width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    object->data->draw_line_width++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", object->data->draw_line_width);

  //---------------------------
}
void Entity::entity_point(entity::Object* object){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Number of points
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Nb point"); ImGui::TableNextColumn();
  string nb_point = math::thousand_separator(object->data->nb_point);
  ImGui::Text("%s", nb_point.c_str());

  //Point size
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Point size"); ImGui::TableNextColumn();
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    object->data->draw_point_size--;

    if(object->data->draw_point_size <= 1){
      object->data->draw_point_size = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    object->data->draw_point_size++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", object->data->draw_point_size);

  //---------------------------
}

}
