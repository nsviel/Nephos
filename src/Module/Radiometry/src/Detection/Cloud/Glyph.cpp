#include "Glyph.h"

#include <Radiometry/Namespace.h>


namespace rad::detection::cloud{

//Constructor / Destructor
Glyph::Glyph(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->rad_struct = node_radio->get_rad_struct();
  this->dat_glyph = node_data->get_dat_glyph();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::draw_sphere_glyph(vec3 pose, float radius){
  //---------------------------

  this->reset_glyph();
  this->draw_glyph(pose, radius);

  //---------------------------
}

//Subfunction
void Glyph::reset_glyph(){
  dat::glyph::object::Sphere* sphere = rad_struct->detection.glyph_calibration;
  //---------------------------

  sphere->reset_glyph();

  //---------------------------
}
void Glyph::draw_glyph(vec3 pose, float radius){
  dat::glyph::object::Sphere* glyph_sphere = rad_struct->detection.glyph_calibration;
  //---------------------------

  glyph_sphere->move_sphere(pose, radius * 2);

  //---------------------------
}


}
