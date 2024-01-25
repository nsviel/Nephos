#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Task;}


class VK_info
{
public:
  //Constructor / Destructor
  VK_info(vk::structure::Vulkan* struct_vulkan);
  ~VK_info();

public:
  //Main functions
  string get_gpu_name();
  float get_fps();
  int* get_fps_max();
  vec4* get_color_background();
  vector<vk::structure::Task>& get_profiler_data();

private:
  vk::structure::Vulkan* struct_vulkan;
};
