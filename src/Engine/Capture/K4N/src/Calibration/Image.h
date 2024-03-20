#pragma once

#include <Utility/Specific/common.h>
#include <opencv2/opencv.hpp>


namespace k4n::hough{

enum Drawing{
  ALL = 0,
  BEST = 1,
};

}

namespace k4n::calibration{

class Image
{
public:
  Image();
  ~Image();

public:
  //Main function
  void draw_all_sphere(utl::media::Image* input, vector<vec3>& vec_circle, utl::media::Image* output);
  void draw_best_sphere(utl::media::Image* input, vector<vec3>& vec_circle, utl::media::Image* output);

private:

};

}
