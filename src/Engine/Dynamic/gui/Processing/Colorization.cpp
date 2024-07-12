#include "Colorization.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace dyn::gui{

//Constructor / Destructor
Colorization::Colorization(dyn::Node* node_dynamic){
  //---------------------------

  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->dyn_colorizer = new dyn::cloud::Colorizer(node_dynamic);

  //---------------------------
}
Colorization::~Colorization(){}

//Main function
void Colorization::design_colorization(utl::base::Element* element){
  if(element == nullptr) return;
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Colorization##dynamic")){

    this->colorization_mode(element);
    ImGui::Separator();
    this->heatmap_mode(element);

    this->option_intensity(element);
    this->option_height(element);

    this->update_element(element);
  }

  //---------------------------
}
void Colorization::update_element(utl::base::Element* element){
  dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element);
  //---------------------------

  if(entity && update_color){
    dyn_colorizer->colorize_object(entity);
    dyn_colorizer->update_object(entity);
    this->update_color = false;
  }

  //---------------------------
}

//Mode function
void Colorization::colorization_mode(utl::base::Element* element){
  //---------------------------

  ImGui::BeginTable("colorization##mode", 2);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("RGB##colorization", &dyn_struct->colorization.color_mode, ope::color::RGB)){
    this->update_color = true;
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("##unicolor", &dyn_struct->colorization.color_mode, ope::color::UNICOLOR)){
    this->update_color = true;
  }
  ImGui::SameLine();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar;
  if(ImGui::ColorEdit4("##unicolor_choice", (float*)&dyn_struct->colorization.unicolor, flags)){
    this->update_color = true;
  }

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("I##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY)){
    this->update_color = true;
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("I inv##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY_INV)){
    this->update_color = true;
  }

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("I cor##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY_COR)){
    this->update_color = true;
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("I cal##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY_CAL)){
    this->update_color = true;
  }

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("N##colorization", &dyn_struct->colorization.color_mode, ope::color::NORMAL)){
    this->update_color = true;
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("It##colorization", &dyn_struct->colorization.color_mode, ope::color::INCIDENCE_ANGLE)){
    this->update_color = true;
  }

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("Heatmap##colorization", &dyn_struct->colorization.color_mode, ope::color::HEATMAP)){
    update_color = true;
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("Structure##colorization", &dyn_struct->colorization.color_mode, ope::color::STRUCTURE)){
    update_color = true;
  }

  ImGui::EndTable();

  //---------------------------
}
void Colorization::heatmap_mode(utl::base::Element* element){
  if(dyn_struct->colorization.color_mode != ope::color::HEATMAP) return;
  //---------------------------

  ImGui::BeginTable("heatmap##mode", 3);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("I##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::INTENSITY)){
    update_color = true;
  }
  ImGui::SameLine();
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("I cor##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::INTENSITY_COR)){
    update_color = true;
  }
  ImGui::SameLine();
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("I cal##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::INTENSITY_CAL)){
    update_color = true;
  }

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("H##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::HEIGHT)){
    update_color = true;
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("R##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::RANGE)){
    update_color = true;
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("It##heatmap", &dyn_struct->colorization.heatmap_mode, ope::color::heatmap::INCIDENCE_ANGLE)){
    update_color = true;
  }

  ImGui::EndTable();

  //---------------------------
}

//Option function
void Colorization::option_intensity(utl::base::Element* element){
  int& mode = dyn_struct->colorization.color_mode;
  int& heatmap = dyn_struct->colorization.heatmap_mode;
  //---------------------------

  //Intensity cursor
  if(mode == ope::color::INTENSITY || mode == ope::color::INTENSITY_INV || mode == ope::color::HEATMAP && heatmap == ope::color::heatmap::INTENSITY){
    ImGui::Separator();
    ImGui::SetNextItemWidth(100);
    ImGui::SliderInt("I diviser", &dyn_struct->operation.intensity.diviser, 1, 10000);
  }

  //---------------------------
}
void Colorization::option_height(utl::base::Element* element){
  if(dyn_struct->colorization.heatmap_mode != ope::color::heatmap::HEIGHT) return;
  //---------------------------

  //Height heatmap
  float min = -10;
  float max = 10;
  ImGui::SetNextItemWidth(125);
  ImGui::DragFloatRange2("Z##321", &dyn_struct->colorization.range_height.x, &dyn_struct->colorization.range_height.y, 0.1f, min, max, "%.1f", "%.1f");

  //---------------------------
}

}
