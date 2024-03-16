#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Task;}
namespace prf::graph{class Tasker;}
namespace prf::vulkan{class Profiler;}


namespace vk::main{

class Info
{
public:
  //Constructor / Destructor
  Info(vk::structure::Vulkan* struct_vulkan);
  ~Info();

public:
  //Profiler vulkan info
  void fill_info();
  void fill_vulkan_info(prf::vulkan::Profiler* prf_vulkan);
  void fill_vulkan_device(prf::vulkan::Profiler* prf_vulkan);

  //Subfunction
  string get_gpu_name();
  vec4* get_color_background();
  bool is_gpu_discrete();

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
