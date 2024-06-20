#include "Operation.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dyn::gui{

//Constructor / Destructor
Operation::Operation(dyn::Node* node_dynamic){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->dat_selection = node_data->get_dat_selection();
  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->dyn_operation = node_dynamic->get_ope_cloud();
  this->dyn_colorization = new dyn::gui::Colorization(node_dynamic);
  this->dyn_transformation = new dyn::gui::Transformation(node_dynamic);
  this->dyn_info = new dyn::gui::Info(node_dynamic);
  this->dyn_config = new dyn::gui::Configuration(node_dynamic);
  this->ope_operation = new ope::Operation();
  this->ope_normal = new ope::normal::KNN();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::design_operation(){
  utl::base::Element* element = dat_selection->get_selected_element();
  if(element == nullptr) return;
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
  //Info
  dyn_info->design_info(element);

  //Configuration
  dyn_config->design_configuration(element);

  //Transformation
  dyn_transformation->design_transformation(element);

  //Colorization
  dyn_colorization->design_colorization(element);

  //Normal
  //this->draw_ope_normal(set);
  ImGui::PopStyleColor();

  //---------------------------
  ImGui::Separator();
}

//Subfunction
void Operation::draw_ope_normal(dat::base::Set* set){
  //---------------------------

  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Normal##dynamic")){

    if(ImGui::Button("Compute##normal", ImVec2(100, 0))){
      utl::base::Data* data = &set->active_entity->data;
      ope_normal->compute_normal(data, dyn_struct->operation.normal.knn);
    }

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
