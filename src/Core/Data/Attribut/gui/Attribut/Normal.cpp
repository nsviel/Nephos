#include "Normal.h"

#include <Data/Attribut/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::atr::gui{

//Constructor / Destructor
Normal::Normal(dat::atr::Node* node_attribut){
  //---------------------------

  this->atr_struct = node_attribut->get_atr_struct();

  //---------------------------
}
Normal::~Normal(){}

//Main function
void Normal::design_header(std::shared_ptr<utl::base::Element> element){
  if(!element) return;
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Normal##attribut")){
    this->draw_static(element);
  }

  //---------------------------
}

//Subfunction
void Normal::draw_static(std::shared_ptr<utl::base::Element> element){
  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  //---------------------------

  //Enable
  ImGui::Button("Compute", ImVec2(100, 0));

  //Parameter: kNN
  ImGui::SetNextItemWidth(100);
  ImGui::SliderInt("kNN", &atr_struct->normal.knn, 1, 10);

  //Computation time
  ImGui::Text("Time");
  ImGui::SameLine();
  ImGui::TextColored(color, "%.2f ms", atr_struct->normal.time);

  //---------------------------
}
void Normal::draw_dynamic(){
  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Normal");

  //Enable
  ImGui::Checkbox("Activated", &atr_struct->normal.enable);

  //Parameter: kNN
  ImGui::SetNextItemWidth(100);
  ImGui::SliderInt("kNN", &atr_struct->normal.knn, 1, 10);

  //Computation time
  ImGui::Text("Time");
  ImGui::SameLine();
  ImGui::TextColored(color, "%.2f ms", atr_struct->normal.time);

  //---------------------------
}

}
