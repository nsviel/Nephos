#ifndef STRUCT_VIDEO_H
#define STRUCT_VIDEO_H

#include <glm/glm.hpp>
#include <string>
#include <vector>


struct Struct_video{
  //---------------------------

  int64_t start_time;
  int64_t duration;
  int64_t bit_rate;
  int fps;
  int width;
  int height;

  //---------------------------
};


#endif
