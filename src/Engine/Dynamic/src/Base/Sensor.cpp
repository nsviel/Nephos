#include "Sensor.h"


namespace dyn::base{

//Main function
void Sensor::init(){
  //---------------------------

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
}
void Sensor::clean(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

}
