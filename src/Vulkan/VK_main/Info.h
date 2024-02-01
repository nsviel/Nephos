#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Task;}
namespace utl::element{class Profiler;}


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
  utl::element::Profiler* get_gpu_profiler();
  int* get_fps_max();
  vec4* get_color_background();

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
