#include "Correction.h"

#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>
#include <Core/Namespace.h>
#include <Utility/Namespace.h>


namespace rad::cor::gui{

//Constructor / Destructor
Correction::Correction(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();
  vk::Node* node_vulkan = node_radio->get_node_vulkan();
  rad::cor::Node* node_correction = node_radio->get_node_correction();

  this->dat_image = node_element->get_dat_image();
  this->rad_struct = node_correction->get_rad_struct();
  this->stream_1 = new dat::img::gui::Stream(node_vulkan);
  this->stream_2 = new dat::img::gui::Stream(node_vulkan);

  //---------------------------
}
Correction::~Correction(){}

//Main function
void Correction::draw_tab(dat::base::Sensor* sensor){
  //---------------------------

  this->display_image(sensor);

  //---------------------------
}

//Subfunction
void Correction::display_image(dat::base::Sensor* sensor){
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
