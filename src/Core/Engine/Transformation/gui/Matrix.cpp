#include "Matrix.h"

#include <Engine/Transformation/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace eng::trf::gui{

//Constructor / Destructor
Matrix::Matrix(){
  //---------------------------

  this->trf_operation = new eng::trf::Operation();
  this->trf_utils = new eng::trf::Utils();

  //---------------------------
}
Matrix::~Matrix(){}

//Main function
void Matrix::design_matrix(std::shared_ptr<utl::base::Element> element){
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Transformation##dynamic")){
    this->draw_operation(element);
    this->draw_matrix(element);
  }

  //---------------------------
}

//Subfunction
void Matrix::draw_operation(std::shared_ptr<utl::base::Element> element){
  utl::base::Pose& pose = *element->pose;
  //---------------------------

  if(ImGui::Button("R##transfomatrix", ImVec2(20, 0))){
    trf_utils->make_transformation_identity(pose.model);
  }
  ImGui::SameLine();
  if(ImGui::Button("C##centerentity", ImVec2(20, 0))){
    trf_operation->center_object(element);
  }
  ImGui::SameLine();
  if(ImGui::Button(ICON_FA_ARROWS_ROTATE "##xrotation", ImVec2(20, 0))){
    trf_operation->make_rotation_X_90d(element, 1);
  }

  //---------------------------
}
void Matrix::draw_matrix(std::shared_ptr<utl::base::Element> element){
  utl::base::Pose& pose = *element->pose;
  //---------------------------

  //Model matrix
  ImVec2 width = ImGui::GetContentRegionAvail();
  glm::mat4& model = pose.model;
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
