#include "Data.h"

#include <Data/Element/Namespace.h>
#include <Engine/Transformation/Namespace.h>
#include <imgui/core/imgui.h>


namespace dat::entity::gui{

//Constructor / Destructor
Data::Data(dat::elm::Node* node_element){
  //---------------------------

  this->dat_entity = node_element->get_dat_entity();
  this->trf_operation = new eng::trf::Operation();

  this->item_width = 100;

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::draw_entity_data(std::shared_ptr<dat::base::Entity> entity){
  if(!entity) return;
  //---------------------------

  this->entity_info(entity);
  this->entity_data(entity);
  this->entity_pose(entity);

  //---------------------------
  ImGui::Separator();
}

//Subfunction
void Data::entity_info(std::shared_ptr<dat::base::Entity> entity){
  //---------------------------

  //Visibility
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Visibility"); ImGui::TableNextColumn();
  utl::base::Data& data = *entity->data;
  if(ImGui::Checkbox("##4555", &data.is_visible)){
    dat_entity->visibility_entity(entity, data.is_visible);
  }

  //Name
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Name"); ImGui::TableNextColumn();
  static char str_n[256];
  strcpy(str_n, entity->name.c_str());
  ImGui::SetNextItemWidth(item_width);
  if(ImGui::InputText("##name", str_n, IM_ARRAYSIZE(str_n), ImGuiInputTextFlags_EnterReturnsTrue)){
    entity->name = str_n;
  }

  //---------------------------
}
void Data::entity_data(std::shared_ptr<dat::base::Entity> entity){
  utl::base::Data& data = *entity->data;
  //---------------------------

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Format"); ImGui::TableNextColumn();
  static char str_f[256];
  strcpy(str_f, data.path.format.c_str());
  ImGui::SetNextItemWidth(item_width);
  if(ImGui::InputText("##format", str_f, IM_ARRAYSIZE(str_f), ImGuiInputTextFlags_EnterReturnsTrue)){
    data.path.format = str_f;
  }

  //---------------------------
}
void Data::entity_pose(std::shared_ptr<dat::base::Entity> entity){
  utl::base::Pose& pose = *entity->pose;
  //---------------------------

  //Root pos
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Root"); ImGui::TableNextColumn();
  ImGui::NextColumn();
  float floatArray[3];
  std::memcpy(floatArray, &pose.root, sizeof(float) * 3);
  if(ImGui::DragFloat3("##434", floatArray, 0.01f, -100.0f, 100.0f, "%.2f")){
    glm::vec3 new_root(floatArray[0], floatArray[1], floatArray[2]);
    trf_operation->make_translation_from_root(entity, new_root);
  }
  ImGui::SameLine();
  if(ImGui::Button("R", ImVec2(15,0))){
    trf_operation->make_translation_from_root(entity, glm::vec3(0, 0, 0));
  }

  //---------------------------
}

}
