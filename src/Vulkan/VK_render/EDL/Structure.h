#pragma once


namespace vk::render::edl{

struct Structure{
  //---------------------------

  bool activated;
  float z_near;
  float z_far;
  float strength;
  float radius;
  int tex_width;
  int tex_height;

  //---------------------------
};

}
