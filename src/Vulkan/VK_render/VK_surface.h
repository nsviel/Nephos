#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/UTL_specific/common.h>


class UTL_window;


class VK_surface
{
public:
  //Constructor / Destructor
  VK_surface(vk::structure::Vulkan* struct_vulkan);
  ~VK_surface();

public:
  //Main functions
  void init();
  void clean();

  //Subfunction
  void check_for_resizing();
  vec2 compute_window_dim();

private:
  vk::structure::Vulkan* struct_vulkan;
};
