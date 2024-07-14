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
  this->gui_normal = new dyn::gui::Normal(node_dynamic);

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
  gui_normal->design_normal();
  ImGui::PopStyleColor();

  //---------------------------
  ImGui::Separator();
}

//Subfunction


}
