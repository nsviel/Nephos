#include "Correction.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>
#include <Core/Namespace.h>
#include <Processing/Namespace.h>


namespace rad::gui::correction{

//Constructor / Destructor
Correction::Correction(rad::Node* node_radio){
  //---------------------------

  core::Node* node_core = node_radio->get_node_core();
  dat::Node* node_data = node_radio->get_node_data();
  rad::correction::Node* node_correction = node_radio->get_node_correction();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->dat_image = node_element->get_dat_image();
  this->rad_struct = node_correction->get_rad_struct();
  this->stream_1 = new rnd::gui::Stream(node_core->get_node_vulkan());
  this->stream_2 = new rnd::gui::Stream(node_core->get_node_vulkan());

  //---------------------------
}
Correction::~Correction(){}

//Main function
void Correction::draw_tab(dyn::prc::base::Sensor* sensor){
  //---------------------------

  this->display_image(sensor);

  //---------------------------
}

//Subfunction
void Correction::display_image(dyn::prc::base::Sensor* sensor){
  ImVec2 available_space = ImGui::GetContentRegionAvail();
  //---------------------------

  utl::media::Image* intensity = dat_image->get_image(sensor, "Intensity");
  utl::media::Image* correction = dat_image->get_image(sensor, "Correction");

  int nb_image = 0;
  nb_image += (intensity != nullptr) ? 1 : 0;
  nb_image += (correction != nullptr) ? 1 : 0;

  //Stream
  stream_1->draw_stream(intensity, ImVec2(available_space.x, available_space.y / nb_image - 5));
  stream_2->draw_stream(correction, ImVec2(available_space.x, available_space.y / nb_image - 5));

  //---------------------------
  ImGui::Separator();
}

}
