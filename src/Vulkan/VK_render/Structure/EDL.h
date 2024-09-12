#pragma once


namespace vk::render::structure{

struct EDL{
  //---------------------------

  bool activated = true;
  float z_near = 0.001;
  float z_far = 1000;
  float strength = 15.0;
  float radius = 1.0;
  int tex_width = 100;
  int tex_height = 100;

  //---------------------------
};

}
