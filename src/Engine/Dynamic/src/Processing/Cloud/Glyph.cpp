#include "Glyph.h"

#include <Dynamic/Namespace.h>


namespace dyn::cloud{

//Constructor / Destructor
Glyph::Glyph(dyn::Node* node_dynamic){
  //---------------------------

  this->dyn_struct = node_dynamic->get_dyn_struct();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::init(){
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

}
