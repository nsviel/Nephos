#include "Operation.h"

#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <Core/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::atr::gui{

//Constructor / Destructor
Operation::Operation(dat::atr::Node* node_attribut){
  //---------------------------

  this->node_core = node_attribut->get_node_core();
  this->ope_image = new dat::img::Converter();
  this->dat_element = new dat::elm::Element();
  this->gui_normal = new dat::atr::gui::Normal(node_attribut);

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::design_operation(utl::base::Element* element){
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Operation##dynamic")){
    gui_normal->design_normal();
    this->draw_ope_image(element);
  }

  //---------------------------
}

//Subfunction
void Operation::draw_ope_image(utl::base::Element* element){
  //---------------------------

  if(ImGui::Button("intensity to image")){
    dat::Node* node_data = node_core->get_node_data();
    dat::elm::Node* node_element = node_data->get_node_element();
    dat::elm::Image* dat_image = node_element->get_dat_image();
    dat::base::Entity* entity = dat_element->get_active_entity(element);
    utl::media::Image* image = dat_image->get_or_create_image(entity, "Intensity");
    ope_image->convert_spherical_pc_to_image(&entity->data, image);
  }


  //---------------------------
}

}
