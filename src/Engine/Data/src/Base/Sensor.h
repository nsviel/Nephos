#pragma once

#include <Data/src/Base/Entity.h>


namespace dat::base{

struct Sensor : public dat::base::Entity{
  //---------------------------

  virtual glm::vec3 convert_depth_2d_to_3d(glm::ivec2 point){return glm::vec3(0);}

  int state_UID = 0;
  std::vector<uint16_t> buffer_depth;
  std::vector<uint16_t> buffer_ir;
  std::vector<glm::vec3> buffer_Nxyz;

/*
  //Sensor glyph
  for(int i=0; i<20; i++){
    dat::glyph::object::Sphere* sphere = new dat::glyph::object::Sphere(node_engine);
    dat_glyph->create_glyph(&object, sphere);
    vec4 color = math::random(i);
    sphere->construct(color);

    this->detection.vec_glyph_sphere.push_back(sphere);
  }
  dat::glyph::object::Sphere* sphere = new dat::glyph::object::Sphere(node_engine);
  this->detection.glyph_calibration = sphere;
  dat_glyph->create_glyph(&object, sphere);
  sphere->construct(vec4(0, 1, 0, 1));
*/

  //---------------------------
};

}
