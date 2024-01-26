#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

namespace vk::structure{class Vulkan;}


namespace vk::instance{

class VK_profiler
{
public:
  //Constructor / Destructor
  VK_profiler(vk::structure::Vulkan* struct_vulkan);
  ~VK_profiler();

public:
  //Main functions
  void start();
  void stop(string name);

private:
  vk::structure::Vulkan* struct_vulkan;
  Timer timer;
  timer_time time_beg;
};

}
