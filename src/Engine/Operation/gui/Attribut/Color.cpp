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
  if(ImGui::RadioButton("Nxyz##colorization", &ope_struct->attribut.color.mode, ope::color::NORMAL)){
    ope_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("Field##colorization", &ope_struct->attribut.color.mode, ope::color::FIELD)){
    ope_colorizer->colorize_element(element);
  }

  //Third line
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("Heatmap##colorization", &ope_struct->attribut.color.mode, ope::color::HEATMAP)){
    ope_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("Structure##colorization", &ope_struct->attribut.color.mode, ope::color::STRUCTURE)){
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
    if(!entity) return;

    std::vector<std::string> vec_field;
    for(int i=0; i<entity->data.vec_field.size(); i++){
      utl::base::Field& field = entity->data.vec_field[i];
      vec_field.push_back(field.name);
    }

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

void Color::mode_option(utl::base::Element* element){
  //---------------------------




  //---------------------------
}

}
