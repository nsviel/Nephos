#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Task;}
namespace prf{class Tasker;}
namespace prf::vulkan{class Manager;}


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
  void fill_vulkan_info(prf::vulkan::Manager* prf_vulkan);
  void fill_vulkan_device(prf::vulkan::Manager* prf_vulkan);

  //Subfunction
  string get_gpu_name();
  vec4* get_color_background();

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
