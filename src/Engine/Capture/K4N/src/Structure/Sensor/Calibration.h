#pragma once

#include <Scene/Namespace.h>
#include <string>


namespace k4n::structure{

struct Calibration{
  //---------------------------

  vector<vec3> vec_circle;
  vector<glyph::scene::Sphere*> vec_sphere_glyph;

  //---------------------------
};

}
