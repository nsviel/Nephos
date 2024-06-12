#include "Correction.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::gui{

//Constructor / Destructor
Correction::Correction(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();
  rad::correction::Node* node_correction = node_radio->get_node_correction();

  this->rad_struct = node_correction->get_rad_struct();
  this->stream = new rnd::Stream(node_engine);

  //---------------------------
}
Correction::~Correction(){}

//Main function
void Correction::draw_tab(dyn::base::Sensor* sensor){
  //---------------------------

  this->display_image();

  //---------------------------
}

//Subfunction
void Correction::display_image(){
  //---------------------------
/*
  ImVec2 image_size = ImGui::GetContentRegionAvail();
  image_size.y -= 5;
  stream->draw_stream(&image, image_size);
*/
  //---------------------------
  ImGui::Separator();
}

}
