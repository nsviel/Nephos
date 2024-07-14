#include "Normal.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dyn::gui{

//Constructor / Destructor
Normal::Normal(dyn::Node* node_dynamic){
  //---------------------------

  this->dyn_struct = node_dynamic->get_dyn_struct();

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
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Operation##dynamic")){
    ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Normal");

    //Enable
    ImGui::Checkbox("Activated", &dyn_struct->operation.normal.enable);

    //Parameter: kNN
    ImGui::SetNextItemWidth(100);
    ImGui::SliderInt("kNN", &dyn_struct->operation.normal.knn, 1, 10);

    //Computation time
    ImGui::Text("Time");
    ImGui::SameLine();
    ImGui::TextColored(color, "%.2f ms", dyn_struct->operation.normal.time);
  }

  //---------------------------
}

}
