#include "Calibration.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Calibration::Calibration(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();

  this->rad_correction = node_radio->get_node_correction-);
  this->rad_struct = rad_correction->get_rad_struct();
  this->stream = new rnd::Stream(node_engine);

  //---------------------------
}
Calibration::~Calibration(){}

//Main function
void Calibration::draw_tab(){
  //---------------------------

  this->display_image();

  //---------------------------
}

//Subfunction
void Calibration::display_image(){
  //---------------------------

  ImVec2 image_size = ImGui::GetContentRegionAvail();
  image_size.y -= 5;
  stream->draw_stream(&rad_struct->image, image_size);

  //---------------------------
  ImGui::Separator();
}

}
