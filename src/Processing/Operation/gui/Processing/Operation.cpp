#include "Operation.h"

#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <Core/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ope::gui{

//Constructor / Destructor
Operation::Operation(ope::Node* node_operation){
  //---------------------------

  this->node_engine = node_operation->get_node_engine();
  this->ope_image = new ope::image::Converter();
  this->dat_element = new dat::Element();
  this->gui_normal = new ope::gui::Normal(node_operation);

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
    dat::Node* node_data = node_engine->get_node_data();
    dat::element::Image* dat_image = node_data->get_dat_image();
    dat::base::Entity* entity = dat_element->get_active_entity(element);
    utl::media::Image* image = dat_image->get_or_create_image(entity, "Intensity");
    ope_image->convert_spherical_pc_to_image(&entity->data, image);
  }


  //---------------------------
}

}
