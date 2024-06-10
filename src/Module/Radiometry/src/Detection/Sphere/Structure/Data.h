#pragma once

#include <Radiometry/src/Detection/Sphere/Structure/Circle.h>
#include <Radiometry/src/Detection/Sphere/Structure/Sphere.h>
#include <Radiometry/src/Detection/Sphere/Glyph/Sphere.h>


namespace rad::detection::structure{

struct Data{
  //---------------------------

  std::vector<rad::detection::structure::Circle> vec_circle;
  std::vector<rad::detection::structure::Sphere> vec_sphere;
  std::vector<rad::detection::glyph::Sphere*> vec_glyph_sphere;

  //---------------------------
};

}
