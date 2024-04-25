#include "Glyph.h"

#include <Kinect/Namespace.h>
#include <Scene/Namespace.h>
#include <Radiometry/Namespace.h>


namespace radio::detection::cloud{

//Constructor / Destructor
Glyph::Glyph(radio::Structure* radio_struct){
  //---------------------------

  this->sce_glyph = radio_struct->node_scene->get_scene_glyph();

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
  glyph::scene::Sphere* sphere = sensor->detection.glyph_calibration;
  //---------------------------

  sphere->reset_glyph();

  //---------------------------
}
void Glyph::draw_glyph(k4n::dev::Sensor* sensor, vec3 pose, float radius){
  glyph::scene::Sphere* glyph_sphere = sensor->detection.glyph_calibration;
  //---------------------------

  glyph_sphere->move_sphere(pose, radius * 2);

  //---------------------------
}


}
