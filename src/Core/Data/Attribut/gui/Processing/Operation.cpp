#include "Operation.h"

#include <Data/Attribut/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Data/Image/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::atr::gui{

//Constructor / Destructor
Operation::Operation(dat::atr::Node* node_attribut){
  //---------------------------

  dat::elm::Node* node_element = node_attribut->get_node_element();

  this->dat_image = node_element->get_dat_image();
  this->img_image = new dat::img::Converter();
  this->dat_element = new dat::elm::Element();
  this->gui_normal = new dat::atr::gui::Normal(node_attribut);

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::design_operation(std::shared_ptr<utl::base::Element> element){
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Operation##dynamic")){
    gui_normal->design_normal();
    this->draw_img_image(element);
  }

  //---------------------------
}

//Subfunction
void Operation::draw_img_image(std::shared_ptr<utl::base::Element> element){
  //---------------------------

  if(ImGui::Button("intensity to image")){
    std::shared_ptr<dat::base::Entity> entity = dat_element->get_active_entity(element);
    std::shared_ptr<utl::media::Image> image = dat_image->get_or_create_image(*entity, "Intensity");
    img_image->convert_spherical_pc_to_image(entity->data, image);
  }


  //---------------------------
}

}
