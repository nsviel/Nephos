#include "Transformation.h"

#include <Dynamic/Namespace.h>
#include <Utility/Namespace.h>


namespace dyn::gui{

//Constructor / Destructor
Transformation::Transformation(dyn::Node* node_dynamic){
  //---------------------------

  this->dyn_struct = node_dynamic->get_dyn_struct();
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
    this->draw_loader(element);
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
void Transformation::draw_loader(utl::base::Element* element){
  //---------------------------

  if(ImGui::Button("Load##transfomatrix", ImVec2(70, 0))){
    //utl::transformation::save_transformation_to_file(pose->model, pose->path);
  }
  ImGui::SameLine();
  if(ImGui::Button("Save##transfomatrix", ImVec2(70, 0))){
    //utl::transformation::save_transformation_to_file(pose->model, pose->path);
  }

  //Path
  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  ImGui::BeginTable("transformation_info##dynamic", 2);

  if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Path"); ImGui::TableNextColumn();

    utl::base::Data* data = &entity->data;
    string path = (data->path.transformation == "") ? "(not defined)" : data->path.transformation;
    ImGui::TextColored(color, "%s", path.c_str());
  }

  ImGui::EndTable();

  //---------------------------
}
void Transformation::draw_matrix(utl::base::Element* element){
  utl::base::Pose* pose = &element->pose;
  //---------------------------

  //Model matrix
  ImVec2 width = ImGui::GetContentRegionAvail();
  mat4& model = pose->model;
  ImGui::Columns(4, "ModelMat");
  for(int i=0; i<4; i++){
    ImGui::Separator();
    for(int j=0;j<4;j++){
      ImGui::Text("%.3f", model[i][j]);
      ImGui::NextColumn();
    }
  }
  ImGui::Separator();
  ImGui::Columns(1);

  //---------------------------
}

}
