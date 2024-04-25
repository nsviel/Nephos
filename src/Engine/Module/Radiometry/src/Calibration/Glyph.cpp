#include "Glyph.h"

#include <K4N/Namespace.h>
#include <Scene/Namespace.h>
#include <Radiometry/Namespace.h>

namespace radio::calibration{

//Constructor / Destructor
Glyph::Glyph(k4n::Node* node_k4n){
  //---------------------------

  eng::scene::Node* node_scene = node_k4n->get_node_scene();

  this->sce_glyph = node_scene->get_scene_glyph();
  this->k4n_transfo = new k4n::utils::Transformation();

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
