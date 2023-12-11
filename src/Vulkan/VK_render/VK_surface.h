#pragma once

#include <UTL_specific/common.h>

class Struct_vulkan;
class UTL_window;


class VK_surface
{
public:
  //Constructor / Destructor
  VK_surface(Struct_vulkan* struct_vulkan);
  ~VK_surface();

public:
  //Main functions
  void init();
  void clean();

  //Subfunction
  void check_for_resizing();
  vec2 compute_window_dim();

private:
  Struct_vulkan* struct_vulkan;
};
