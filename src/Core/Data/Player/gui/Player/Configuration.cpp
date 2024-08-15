#include "Configuration.h"

#include <imgui/core/imgui.h>


namespace dat::ply::gui{

//Constructor / Destructor
Configuration::Configuration(){
  //---------------------------



  //---------------------------
}
Configuration::~Configuration(){}

//Main function
void Configuration::design_configuration(utl::base::Element* element){
  /*dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(element);
  if(sensor == nullptr) return;
  //---------------------------

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetStyle().ItemSpacing.y);
  if(ImGui::CollapsingHeader("Configuration##dynamic")){
    this->sensor_config(sensor);
  }
*/
  //---------------------------
}

//Subfunction
void Configuration::sensor_config(dyn::base::Sensor* sensor){

  //---------------------------

  //sensor->gui_config();

  //---------------------------
  ImGui::Separator();
}

}
