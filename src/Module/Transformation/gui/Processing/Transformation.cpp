#include "Transformation.h"

#include <Transformation/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ope::gui{

//Constructor / Destructor
Transformation::Transformation(){
  //---------------------------

  this->ope_operation = new ope::Operation();

  //---------------------------
}
Transformation::~Transformation(){}

//Main function
void Transformation::design_transformation(utl::base::Element* element){
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Transformation##dynamic")){
    this->draw_operation(element);
    this->draw_matrix(element);
  }

  //---------------------------
}

//Subfunction
void Transformation::draw_operation(utl::base::Element* element){
  utl::base::Pose* pose = &element->pose;
  //---------------------------

  if(ImGui::Button("R##transfomatrix", ImVec2(20, 0))){
    utl::transformation::make_transformation_identity(pose->model);
  }
  ImGui::SameLine();
  if(ImGui::Button("C##centerentity", ImVec2(20, 0))){
    ope_operation->center_object(element);
  }
  ImGui::SameLine();
  if(ImGui::Button(ICON_FA_ARROWS_ROTATE "##xrotation", ImVec2(20, 0))){
    ope_operation->make_rotation_X_90d(element, 1);
  }

  //---------------------------
}
void Transformation::draw_matrix(utl::base::Element* element){
  utl::base::Pose* pose = &element->pose;
  //---------------------------

  //Model matrix
  ImVec2 width = ImGui::GetContentRegionAvail();
  glm::mat4& model = pose->model;
  ImGui::Columns(4, "ModelMat");
  for(int i=0; i<4; i++){
    ImGui::Separator();
    for(int j=0;j<4;j++){
      ImGui::Text("%.3f", model[i][j]);
      ImGui::NextColumn();
    }
  }
  ImGui::Columns(1);

  //---------------------------
  ImGui::Separator();
}

}
