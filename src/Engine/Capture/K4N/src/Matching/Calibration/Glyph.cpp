#include "Glyph.h"

#include <K4N/Namespace.h>
#include <Scene/Namespace.h>


namespace k4n::calibration{

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
  glyph::scene::Sphere* glyph_sphere = sensor->detection.glyph_calibration;
  //---------------------------

  //Add sphere radius to the detected circle center
  vec3 dir = glm::normalize(pose);
  pose = pose + dir * radius;

  //Position sphere
  glyph_sphere->move_sphere(pose, radius * 2);

  //---------------------------
}


}
