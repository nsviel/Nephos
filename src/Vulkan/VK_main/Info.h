#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Task;}


namespace vk::main{

class Info
{
public:
  //Constructor / Destructor
  Info(vk::structure::Vulkan* struct_vulkan);
  ~Info();

public:
  //Main functions
  string get_gpu_name();
  float get_fps();
  int* get_fps_max();
  vec4* get_color_background();
  vector<utl::type::Task>& get_profiler_data();

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
