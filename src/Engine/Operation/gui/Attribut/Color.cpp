#include "Color.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace ope::gui{

//Constructor / Destructor
Color::Color(ope::Node* node_operation){
  //---------------------------

  this->ope_struct = node_operation->get_ope_struct();
  this->ope_colorizer = new ope::color::Routine(node_operation);

  //---------------------------
}
Color::~Color(){}

//Main function
void Color::design_colorization(utl::base::Element* element){
  if(element == nullptr) return;
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Colorization##dynamic")){
    //Mode
    this->color_mode(element);
    this->heatmap_mode(element);

    //Option
    this->mode_field_option(element);
    this->mode_option(element);
  }

  //---------------------------
}

//Subfunction
void Color::color_mode(utl::base::Element* element){
  //---------------------------

  ImGui::BeginTable("colorization##mode", 2);

  //First line
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("RGB##colorization", &ope_struct->attribut.color.mode, ope::color::RGB)){
    ope_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("##unicolor", &ope_struct->attribut.color.mode, ope::color::UNICOLOR)){
    ope_colorizer->colorize_element(element);
  }
  ImGui::SameLine();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar;
  if(ImGui::ColorEdit4("##unicolor_choice", (float*)&ope_struct->attribut.color.unicolor, flags)){
    ope_colorizer->colorize_element(element);
  }

  //Second line
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("XYZ##colorization", &ope_struct->attribut.color.mode, ope::color::LOCATION)){
    ope_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("Nxyz##colorization", &ope_struct->attribut.color.mode, ope::color::NORMAL)){
    ope_colorizer->colorize_element(element);
  }

  //Third line
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("Field##colorization", &ope_struct->attribut.color.mode, ope::color::FIELD)){
    ope_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("Structure##colorization", &ope_struct->attribut.color.mode, ope::color::STRUCTURE)){
    ope_colorizer->colorize_element(element);
  }

  //Fourth line
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("Heatmap##colorization", &ope_struct->attribut.color.mode, ope::color::HEATMAP)){
    ope_colorizer->colorize_element(element);
  }

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Color::heatmap_mode(utl::base::Element* element){
  if(ope_struct->attribut.color.mode != ope::color::HEATMAP) return;
  //---------------------------

  ImGui::BeginTable("heatmap##mode", 3);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("I##heatmap", &ope_struct->attribut.heatmap.mode, ope::heatmap::INTENSITY)){
    ope_colorizer->colorize_element(element);
  }
  ImGui::SameLine();
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("I cor##heatmap", &ope_struct->attribut.heatmap.mode, ope::heatmap::INTENSITY_COR)){
    ope_colorizer->colorize_element(element);
  }
  ImGui::SameLine();
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("I cal##heatmap", &ope_struct->attribut.heatmap.mode, ope::heatmap::INTENSITY_CAL)){
    ope_colorizer->colorize_element(element);
  }

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("H##heatmap", &ope_struct->attribut.heatmap.mode, ope::heatmap::HEIGHT)){
    ope_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("R##heatmap", &ope_struct->attribut.heatmap.mode, ope::heatmap::RANGE)){
    ope_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("It##heatmap", &ope_struct->attribut.heatmap.mode, ope::heatmap::INCIDENCE_ANGLE)){
    ope_colorizer->colorize_element(element);
  }

  ImGui::EndTable();

  //---------------------------
}
void Color::mode_field_option(utl::base::Element* element){
  //---------------------------

  if(ope_struct->attribut.color.mode == ope::color::FIELD){
    dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element);
    if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
      entity = set->active_entity;
    }

    std::vector<std::string> vec_field;
    for(int i=0; i<entity->data.vec_field.size(); i++){
      utl::base::Field& field = entity->data.vec_field[i];
      vec_field.push_back(field.name);
    }

    if(ImGui::BeginCombo("##shader_combo_class", vec_field[0].c_str())){
      for(int i=0; i<vec_field.size(); ++i){
        const bool is_selected = (0 == i);
        if(ImGui::Selectable(vec_field[i].c_str(), is_selected)){

        }

        if(is_selected){
          ImGui::SetItemDefaultFocus();
        }
      }

      ImGui::EndCombo();
    }
  }

  //---------------------------
}

void Color::mode_option(utl::base::Element* element){
  //---------------------------

/*
  //Intensity cursor
  if(mode == ope::color::INTENSITY || mode == ope::color::INTENSITY_INV || mode == ope::color::HEATMAP && heatmap == ope::heatmap::INTENSITY){
    ImGui::Separator();
    ImGui::SetNextItemWidth(100);
    ImGui::SliderInt("I diviser", &ope_struct->attribut.intensity.diviser, 1, 10000);
  }
*/

  if(ope_struct->attribut.heatmap.mode != ope::heatmap::HEIGHT) return;
  //Height heatmap
  float min = -10;
  float max = 10;
  ImGui::SetNextItemWidth(125);
  ImGui::DragFloatRange2("Z##321", &ope_struct->attribut.color.range.x, &ope_struct->attribut.color.range.y, 0.1f, min, max, "%.1f", "%.1f");

  //---------------------------
}

}