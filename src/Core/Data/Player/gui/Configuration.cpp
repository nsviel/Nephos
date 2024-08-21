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
  /*dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(element);
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
void Configuration::sensor_config(dat::base::Sensor* sensor){

  //---------------------------

  //sensor->gui_config();

  //---------------------------
  ImGui::Separator();
}

}
