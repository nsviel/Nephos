#include "Glyph.h"

#include <Kinect/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::detection::cloud{

//Constructor / Destructor
Glyph::Glyph(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->radio_struct = node_radio->get_radio_struct();
  this->dat_glyph = node_data->get_data_glyph();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::draw_sphere_glyph(dat::base::Sensor* sensor, vec3 pose, float radius){
  //---------------------------

  this->reset_glyph(sensor);
  this->draw_glyph(sensor, pose, radius);

  //---------------------------
}

//Subfunction
void Glyph::reset_glyph(dat::base::Sensor* sensor){
  dat::glyph::object::Sphere* sphere = radio_struct->detection.glyph_calibration;
  //---------------------------

  sphere->reset_glyph();

  //---------------------------
}
void Glyph::draw_glyph(dat::base::Sensor* sensor, vec3 pose, float radius){
  dat::glyph::object::Sphere* glyph_sphere = radio_struct->detection.glyph_calibration;
  //---------------------------

  glyph_sphere->move_sphere(pose, radius * 2);

  //---------------------------
}


}
