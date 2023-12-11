#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>


class UTL_window;


class VK_surface
{
public:
  //Constructor / Destructor
  VK_surface(vk::structure::Struct_vulkan* struct_vulkan);
  ~VK_surface();

public:
  //Main functions
  void init();
  void clean();

  //Subfunction
  void check_for_resizing();
  vec2 compute_window_dim();

private:
  vk::structure::Struct_vulkan* struct_vulkan;
};
