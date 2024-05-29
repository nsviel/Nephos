#include "Calibration.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Calibration::Calibration(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();

  this->rad_struct = node_radio->get_rad_struct();
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

  utl::media::Image* image = &rad_struct->detection.image;




  ImVec2 image_size = ImGui::GetContentRegionAvail();
  image_size.y -= 5;
  stream->draw_stream(&rad_struct->correction.image, image_size);

  //---------------------------
  ImGui::Separator();
}

}
