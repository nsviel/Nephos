#include "Entity.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <image/IconsFontAwesome6.h>


namespace gui::rnd::data{

//Constructor / Destructor
Entity::Entity(GUI* gui, bool* panel_show){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::scene::Node* eng_data = engine->get_eng_data();
  this->eng_scene = eng_data->get_scene();
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
  //---------------------------

  this->object_title(entity);
  this->object_button(entity);
  this->object_parameter(entity);

  //---------------------------
}

//Subfunction
void Entity::object_title(eng::data::Entity* entity){
  //---------------------------

  this->panel_name = "[Entity::" + entity->type + "]   " + entity->name;

  //---------------------------
}
void Entity::object_button(eng::data::Entity* entity){
  //---------------------------

  //Suppression
  if(entity->is_suppressible){
    if(ImGui::Button(ICON_FA_TRASH "##4567")){
      eng_scene->delete_entity(entity);
      this->entity = nullptr;
    }
  }

  //Centered
  ImGui::SameLine();
  if(ImGui::Button("C##399", ImVec2(20, 0))){
    //ope_operation->center_object(entity);
  }

  //---------------------------
}
void Entity::object_parameter(eng::data::Entity* entity){
  //---------------------------

  if(ImGui::BeginTable("entity##table", 2, ImGuiTableFlags_BordersInnerV)){
    //Visibility
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Visibility"); ImGui::TableNextColumn();
    ImGui::Checkbox("##4555", &entity->is_visible);

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
    if(entity->type == "Object"){
      ImGui::TableNextRow(); ImGui::TableNextColumn();
      ImGui::Text("Format"); ImGui::TableNextColumn();
      static char str_f[256];
      strcpy(str_f, object->file_format.c_str());
      ImGui::SetNextItemWidth(item_width);
      if(ImGui::InputText("##format", str_f, IM_ARRAYSIZE(str_f), ImGuiInputTextFlags_EnterReturnsTrue)){
        object->file_format = str_f;
      }
    }

    //Uniform collection color
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Color"); ImGui::TableNextColumn();
    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs;
    flags |= ImGuiColorEditFlags_AlphaBar;
    if(ImGui::ColorEdit4("Color", (float*)&object->unicolor, flags)){
      ope_attribut->set_unicolor(object);
      eng_scene->update_object(object);
    }

    //Root pos
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    vec3& root = object->root;
    ImGui::Text("Root"); ImGui::TableNextColumn();
    ImGui::NextColumn();
    ImGui::Text("%.2f  %.2f  %.2f", root.x, root.y, root.z);
    ImGui::SameLine();
    if(ImGui::Button("R", ImVec2(15,0))){
      root = vec3(0,0,0);
    }

    //Primitive size
    if(object->draw_type_name == "point"){


      this->object_point(object);
    }
    else if(object->draw_type_name == "line"){
      this->object_line(object);
    }

    ImGui::EndTable();
  }

  //---------------------------
}

//Primitive size
void Entity::object_line(eng::data::Object* object){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Line width
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Line width"); ImGui::TableNextColumn();
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    object->draw_line_width--;

    if(object->draw_line_width <= 1){
      object->draw_line_width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    object->draw_line_width++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", object->draw_line_width);

  //---------------------------
}
void Entity::object_point(eng::data::Object* object){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Number of points
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Nb point"); ImGui::TableNextColumn();
  string nb_point = math::thousand_separator(object->nb_point);
  ImGui::Text("%s", nb_point.c_str());

  //Point size
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Point size"); ImGui::TableNextColumn();
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    object->draw_point_size--;

    if(object->draw_point_size <= 1){
      object->draw_point_size = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    object->draw_point_size++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", object->draw_point_size);

  //---------------------------
}

}
