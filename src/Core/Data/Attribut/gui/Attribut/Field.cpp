#include "Field.h"

#include <Data/Attribut/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::atr::gui{

//Constructor / Destructor
Field::Field(dat::atr::Node* node_attribut){
  //---------------------------

  this->atr_struct = node_attribut->get_atr_struct();

  //---------------------------
}
Field::~Field(){}

//Main function
void Field::design_field(){
  //---------------------------

  this->draw_parameter();

  //---------------------------
}

//Subfunction
void Field::draw_parameter(){
  //---------------------------

  ImVec4 color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Field");



  //---------------------------
}

}
