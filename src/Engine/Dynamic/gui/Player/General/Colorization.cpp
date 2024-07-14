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

    //Main mode
    this->colorization_mode(element);
    ImGui::Separator();
    this->heatmap_mode(element);

    //Mode option
    this->option_intensity(element);
    this->option_height(element);
  }

  //---------------------------
}

//Mode function
void Colorization::colorization_mode(utl::base::Element* element){
  //---------------------------

  ImGui::BeginTable("colorization##mode", 2);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("RGB##colorization", &dyn_struct->colorization.color_mode, ope::color::RGB)){
    dyn_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("##unicolor", &dyn_struct->colorization.color_mode, ope::color::UNICOLOR)){
    dyn_colorizer->colorize_element(element);
  }
  ImGui::SameLine();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar;
  if(ImGui::ColorEdit4("##unicolor_choice", (float*)&dyn_struct->colorization.unicolor, flags)){
    dyn_colorizer->colorize_element(element);
  }

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("I##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY)){
    dyn_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("I inv##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY_INV)){
    dyn_colorizer->colorize_element(element);
  }

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("I cor##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY_COR)){
    dyn_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("I cal##colorization", &dyn_struct->colorization.color_mode, ope::color::INTENSITY_CAL)){
    dyn_colorizer->colorize_element(element);
  }

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("N##colorization", &dyn_struct->colorization.color_mode, ope::color::NORMAL)){
    dyn_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("It##colorization", &dyn_struct->colorization.color_mode, ope::color::INCIDENCE_ANGLE)){
    dyn_colorizer->colorize_element(element);
  }

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("Heatmap##colorization", &dyn_struct->colorization.color_mode, ope::color::HEATMAP)){
    dyn_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("Structure##colorization", &dyn_struct->colorization.color_mode, ope::color::STRUCTURE)){
    dyn_colorizer->colorize_element(element);
  }

  ImGui::EndTable();

  //---------------------------
}
void Colorization::heatmap_mode(utl::base::Element* element){
  if(dyn_struct->colorization.color_mode != ope::color::HEATMAP) return;
  //---------------------------

  ImGui::BeginTable("heatmap##mode", 3);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("I##heatmap", &dyn_struct->colorization.heatmap_mode, ope::heatmap::INTENSITY)){
    dyn_colorizer->colorize_element(element);
  }
  ImGui::SameLine();
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("I cor##heatmap", &dyn_struct->colorization.heatmap_mode, ope::heatmap::INTENSITY_COR)){
    dyn_colorizer->colorize_element(element);
  }
  ImGui::SameLine();
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("I cal##heatmap", &dyn_struct->colorization.heatmap_mode, ope::heatmap::INTENSITY_CAL)){
    dyn_colorizer->colorize_element(element);
  }

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::RadioButton("H##heatmap", &dyn_struct->colorization.heatmap_mode, ope::heatmap::HEIGHT)){
    dyn_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("R##heatmap", &dyn_struct->colorization.heatmap_mode, ope::heatmap::RANGE)){
    dyn_colorizer->colorize_element(element);
  }
  ImGui::TableNextColumn();
  if(ImGui::RadioButton("It##heatmap", &dyn_struct->colorization.heatmap_mode, ope::heatmap::INCIDENCE_ANGLE)){
    dyn_colorizer->colorize_element(element);
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
  if(mode == ope::color::INTENSITY || mode == ope::color::INTENSITY_INV || mode == ope::color::HEATMAP && heatmap == ope::heatmap::INTENSITY){
    ImGui::Separator();
    ImGui::SetNextItemWidth(100);
    ImGui::SliderInt("I diviser", &dyn_struct->operation.intensity.diviser, 1, 10000);
  }

  //---------------------------
}
void Colorization::option_height(utl::base::Element* element){
  if(dyn_struct->colorization.heatmap_mode != ope::heatmap::HEIGHT) return;
  //---------------------------

  //Height heatmap
  float min = -10;
  float max = 10;
  ImGui::SetNextItemWidth(125);
  ImGui::DragFloatRange2("Z##321", &dyn_struct->colorization.range_height.x, &dyn_struct->colorization.range_height.y, 0.1f, min, max, "%.1f", "%.1f");

  //---------------------------
}

}
