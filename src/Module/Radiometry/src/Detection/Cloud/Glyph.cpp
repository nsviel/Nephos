#include "Glyph.h"

#include <Kinect/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::detection::cloud{

//Constructor / Destructor
Glyph::Glyph(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->dat_glyph = node_data->get_glyph();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::draw_sphere_glyph(k4n::dev::Sensor* sensor, vec3 pose, float radius){
  //---------------------------

  this->reset_glyph(sensor);
  this->draw_glyph(sensor, pose, radius);

  //---------------------------
}

//Subfunction
void Glyph::reset_glyph(k4n::dev::Sensor* sensor){
  dat::glyph::object::Sphere* sphere = sensor->detection.glyph_calibration;
  //---------------------------

  sphere->reset_glyph();

  //---------------------------
}
void Glyph::draw_glyph(k4n::dev::Sensor* sensor, vec3 pose, float radius){
  dat::glyph::object::Sphere* glyph_sphere = sensor->detection.glyph_calibration;
  //---------------------------

  glyph_sphere->move_sphere(pose, radius * 2);

  //---------------------------
}


}
