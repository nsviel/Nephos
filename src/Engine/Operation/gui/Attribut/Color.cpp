#include "Color.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace ope::gui{

//Constructor / Destructor
Color::Color(ope::Node* node_operation){
  //---------------------------

  this->ope_struct = node_operation->get_ope_struct();
  this->ope_color = new ope::attribut::Color(node_operation);
  this->dat_element = new dat::Element();
  this->utl_attribut = new utl::base::Attribut();

  //---------------------------
}
Color::~Color(){}

//Main function
void Color::design_colorization(utl::base::Element* element){
  if(element == nullptr) return;
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Colorization##dynamic")){
    this->color_mode(element);
    this->color_option(element);
  }

  //---------------------------
}


//REVOIR CETTE FUNCTION
//diviser color mode
//mettre color option logic dans src

//Subfunction
void Color::color_mode(utl::base::Element* element){
  //---------------------------

  ImGui::BeginTable("colorization##mode", 2);

  //First line
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  this->color_mode_rgb(element);
  ImGui::TableNextColumn();
  this->color_mode_unicolor(element);

  //Second line
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  this->color_mode_normal(element);
  ImGui::TableNextColumn();
  this->color_mode_structure(element);

  //Third line
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  this->color_mode_field(element);
  ImGui::TableNextColumn();
  this->color_mode_heatmap(element);

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Color::color_mode_rgb(utl::base::Element* element){
  dat::base::Entity* entity = dat_element->get_active_entity(element);
  if(!entity) return;
  //---------------------------

  bool condition = (entity->data.rgb.size() != 0);
  if(condition) ImGui::BeginDisabled();

  if(ImGui::RadioButton("RGB##colorization", &ope_struct->attribut.color.mode, ope::color::RGB)){
    ope_color->make_colorization(element);
  }

  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Color::color_mode_unicolor(utl::base::Element* element){
  //---------------------------

  if(ImGui::RadioButton("##unicolor", &ope_struct->attribut.color.mode, ope::color::UNICOLOR)){
    ope_color->make_colorization(element);
  }
  ImGui::SameLine();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar;
  if(ImGui::ColorEdit4("##unicolor_choice", (float*)&ope_struct->attribut.color.unicolor, flags)){
    ope_color->make_colorization(element);
  }

  //---------------------------
}
void Color::color_mode_normal(utl::base::Element* element){
  dat::base::Entity* entity = dat_element->get_active_entity(element);
  if(!entity) return;
  //---------------------------

  bool condition = (entity->data.Nxyz.size() != 0);
  if(condition) ImGui::BeginDisabled();

  if(ImGui::RadioButton("Nxyz##colorization", &ope_struct->attribut.color.mode, ope::color::NORMAL)){
    ope_color->make_colorization(element);
  }

  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Color::color_mode_field(utl::base::Element* element){
  dat::base::Entity* entity = dat_element->get_active_entity(element);
  if(!entity) return;
  //---------------------------

  bool condition = (entity->data.vec_field.size() != 0);
  if(condition) ImGui::BeginDisabled();

  if(ImGui::RadioButton("Field##colorization", &ope_struct->attribut.color.mode, ope::color::FIELD)){
    ope_color->make_colorization(element);
  }

  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Color::color_mode_heatmap(utl::base::Element* element){
  dat::base::Entity* entity = dat_element->get_active_entity(element);
  if(!entity) return;
  //---------------------------

  bool condition = (entity->data.vec_field.size() != 0);
  if(condition) ImGui::BeginDisabled();

  if(ImGui::RadioButton("Heatmap##colorization", &ope_struct->attribut.color.mode, ope::color::HEATMAP)){
    ope_color->make_colorization(element);
  }

  if(condition) ImGui::EndDisabled();

  //---------------------------
}
void Color::color_mode_structure(utl::base::Element* element){
  dat::base::Entity* entity = dat_element->get_active_entity(element);
  if(!entity) return;
  //---------------------------

  bool condition = (entity->data.width != -1);
  if(condition) ImGui::BeginDisabled();

  if(ImGui::RadioButton("Structure##colorization", &ope_struct->attribut.color.mode, ope::color::STRUCTURE)){
    ope_color->make_colorization(element);
  }

  if(condition) ImGui::EndDisabled();

  //---------------------------
}



void Color::color_option(utl::base::Element* element){
  //---------------------------

  if(ope_struct->attribut.color.mode == ope::color::FIELD || ope_struct->attribut.color.mode == ope::color::HEATMAP){
    dat::base::Entity* entity = dat_element->get_active_entity(element);
    if(!entity) return;

    //Prepare vector of field names
    std::vector<std::string> vec_field;
    for(int i=0; i<entity->data.vec_field.size(); i++){
      utl::base::Field& field = entity->data.vec_field[i];
      vec_field.push_back(field.name);
    }

    //Init
    if(entity->data.vec_field.size() != 0 && ope_struct->attribut.color.field == ""){
      ope_struct->attribut.color.field = vec_field[0];
      ope_struct->attribut.color.range = utl_attribut->get_field_range(&entity->data, vec_field[0]);
    }

    //Combo field name
    static int selection = 0;
    ImGui::SetNextItemWidth(150);
    if(ImGui::BeginCombo("##shader_combo_class", vec_field[selection].c_str())){
      for(int i=0; i<vec_field.size(); ++i){
        std::string& field = vec_field[i];
        const bool is_selected = (selection == i);

        if(ImGui::Selectable(field.c_str(), is_selected)){
          ope_struct->attribut.color.field = field;
          ope_struct->attribut.color.range = utl_attribut->get_field_range(&entity->data, field);
          selection = i;
        }

        if(is_selected){
          ImGui::SetItemDefaultFocus();
        }
      }

      ImGui::EndCombo();
    }

    //Range
    ImGui::SetNextItemWidth(150);
    glm::vec2 range = utl_attribut->get_field_range(&entity->data, ope_struct->attribut.color.field);
    float sensitivity = (range.y - range.x) / 100.0f;
    ImGui::DragFloatRange2("Range##321", &ope_struct->attribut.color.range.x, &ope_struct->attribut.color.range.y, sensitivity, range.x, range.y, "%.2f", "%.2f");
  }

  //---------------------------
}

}
