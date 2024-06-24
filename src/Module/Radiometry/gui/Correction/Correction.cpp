#include "Correction.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>
#include <Dynamic/Namespace.h>


namespace rad::gui::correction{

//Constructor / Destructor
Correction::Correction(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();
  dat::Node* node_data = node_radio->get_node_data();
  rad::correction::Node* node_correction = node_radio->get_node_correction();

  this->dat_image = node_data->get_dat_image();
  this->rad_struct = node_correction->get_rad_struct();
  this->stream_1 = new rnd::Stream(node_engine);
  this->stream_2 = new rnd::Stream(node_engine);

  //---------------------------
}
Correction::~Correction(){}

//Main function
void Correction::draw_tab(dyn::base::Sensor* sensor){
  //---------------------------

  this->display_image(sensor);

  //---------------------------
}

//Subfunction
void Correction::display_image(dyn::base::Sensor* sensor){
  ImVec2 available_space = ImGui::GetContentRegionAvail();
  //---------------------------

  utl::media::Image* intensity = dat_image->get_image(sensor, utl::media::INTENSITY);
  utl::media::Image* correction = dat_image->get_image(sensor, utl::media::CORRECTION);

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
