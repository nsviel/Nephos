#include "Cloud.h"

#include <Radiometry/Namespace.h>


namespace rad::detection::glyph{

//Constructor / Destructor
Cloud::Cloud(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->rad_struct = node_radio->get_rad_struct();

  //---------------------------
}
Cloud::~Cloud(){}

//Main function
void Cloud::create_glyph(){
  //---------------------------
/*
  //Sensor glyph
  for(int i=0; i<20; i++){
    rad::detection::glyph::Sphere* sphere = new rad::detection::glyph::Sphere(node_engine);
    dat_glyph->create_glyph(&object, sphere);
    vec4 color = math::random(i);
    sphere->construct(color);

    this->detection.vec_glyph_sphere.push_back(sphere);
  }

  rad::detection::glyph::Sphere* sphere = new rad::detection::glyph::Sphere(node_engine);
  this->detection.glyph_calibration = sphere;
  dat_glyph->create_glyph(&object, sphere);
  sphere->construct(vec4(0, 1, 0, 1));
*/
  //---------------------------
}
void Cloud::draw_sphere_glyph(vec3 pose, float radius){
  //---------------------------

  this->reset_glyph();
  this->draw_glyph(pose, radius);

  //---------------------------
}

//Subfunction
void Cloud::reset_glyph(){
  rad::detection::glyph::Sphere* sphere = rad_struct->detection.glyph_calibration;
  //---------------------------

  sphere->reset_glyph();

  //---------------------------
}
void Cloud::draw_glyph(vec3 pose, float radius){
  rad::detection::glyph::Sphere* glyph_sphere = rad_struct->detection.glyph_calibration;
  //---------------------------

  glyph_sphere->move_sphere(pose, radius * 2);

  //---------------------------
}


}
