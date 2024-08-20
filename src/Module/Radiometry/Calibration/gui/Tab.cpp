#include "Tab.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Processing/Namespace.h>


namespace rad::gui::calibration{

//Constructor / Destructor
Tab::Tab(rad::Node* node_radio){
  //---------------------------

  this->gui_detection = new rad::gui::calibration::Detection(node_radio);

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::design_tab(dyn::prc::base::Sensor* sensor){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(39, 74, 90, 255));
  ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(54, 112, 131, 255));
  ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(44, 101, 131, 255));
  ImGui::BeginTabBar("devices_tab##4567");

  this->tab_detection(sensor);
  this->tab_modeld(sensor);
  this->tab_calibration(sensor);

  ImGui::EndTabBar();
  ImGui::PopStyleColor(3);

  //---------------------------
}

//Subfunction
void Tab::tab_detection(dyn::prc::base::Sensor* sensor){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x/3-3.33);
  if(ImGui::BeginTabItem("Detection##calibration_tab")){
    gui_detection->draw_tab(sensor);

    ImGui::EndTabItem();
  }

  //---------------------------
}
void Tab::tab_modeld(dyn::prc::base::Sensor* sensor){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x/3-3.33);
  if(ImGui::BeginTabItem("Measure##calibration_tab")){


    ImGui::EndTabItem();
  }

  //---------------------------
}
void Tab::tab_calibration(dyn::prc::base::Sensor* sensor){
  //---------------------------

  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x/3-3.33);
  if(ImGui::BeginTabItem("Model##calibration_tab")){


    ImGui::EndTabItem();
  }

  //---------------------------
}

}
