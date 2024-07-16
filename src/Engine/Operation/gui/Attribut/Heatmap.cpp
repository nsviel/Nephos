#include "Heatmap.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace ope::gui{

//Constructor / Destructor
Heatmap::Heatmap(ope::Node* node_operation){
  //---------------------------

  this->ope_struct = node_operation->get_ope_struct();
  this->ope_colorizer = new ope::color::Routine(node_operation);

  //---------------------------
}
Heatmap::~Heatmap(){}

//Main function
void Heatmap::heatmap_mode(utl::base::Element* element){
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


}
