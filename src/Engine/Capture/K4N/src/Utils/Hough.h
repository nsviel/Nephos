#pragma once

#include <Utility/Specific/common.h>


namespace k4n::hough{

enum Mode{
  GRADIENT = 0,
  STANDARD = 1,
  PROBABILISTIC = 2,
};

}

namespace k4n::utils{

class Hough
{
public:
  Hough();
  ~Hough();

public:
  //Sphere fitting
  void find_sphere_in_image(utl::media::Image* image);
  void find_sphere_in_image_with_canny(utl::media::Image* image);

private:
  int mode = k4n::hough::GRADIENT;
};

}
