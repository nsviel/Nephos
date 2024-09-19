#pragma once


namespace vk::geometry{

struct Dynamic{
  //---------------------------

  float depth_scale = 1;
  float depth_offset = 0;
  int tex_depth_width = 100;
  int tex_depth_height = 100;

  //---------------------------
};

}
