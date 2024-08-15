#include "Normal.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
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
void Normal::design_normal(){
  //---------------------------

  this->draw_parameter();

  //---------------------------
}

//Subfunction
void Normal::draw_parameter(){
  //---------------------------

  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Normal");

  //Enable
  ImGui::Checkbox("Activated", &atr_struct->attribut.normal.enable);

  //Parameter: kNN
  ImGui::SetNextItemWidth(100);
  ImGui::SliderInt("kNN", &atr_struct->attribut.normal.knn, 1, 10);

  //Computation time
  ImGui::Text("Time");
  ImGui::SameLine();
  ImGui::TextColored(color, "%.2f ms", atr_struct->attribut.normal.time);

  //---------------------------
}

}
