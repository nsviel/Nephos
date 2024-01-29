#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

namespace vk::structure{class Vulkan;}


namespace vk::instance{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler(vk::structure::Vulkan* struct_vulkan);
  ~Profiler();

public:
  //Main functions
  void start();
  void stop(string name);

private:
  vk::structure::Vulkan* struct_vulkan;
  utl::Timer timer;
  timer_time time_beg;
};

}
