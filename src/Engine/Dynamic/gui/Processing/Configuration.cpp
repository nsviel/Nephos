#include "Configuration.h"

#include <Dynamic/Namespace.h>


namespace dyn::gui{

//Constructor / Destructor
Configuration::Configuration(dyn::Node* node_dynamic){
  //---------------------------



  //---------------------------
}
Configuration::~Configuration(){}

//Main function
void Configuration::design_configuration(utl::base::Element* element){
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Configuration##dynamic")){

  }

  //---------------------------
}

//Subfunction


}
