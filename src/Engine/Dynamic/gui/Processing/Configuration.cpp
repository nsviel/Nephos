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
    this->sensor_config(element);
  }

  //---------------------------
}

//Subfunction
void Configuration::sensor_config(utl::base::Element* element){
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(element);
  if(sensor == nullptr) return;
  //---------------------------

  sensor->gui_config();

  //---------------------------
  ImGui::Separator();
}

}
