#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Task;}
namespace prf::graph{class Tasker;}
namespace prf::hardware{class Profiler;}


namespace vk::main{

class Interface
{
public:
  //Constructor / Destructor
  Interface(vk::structure::Vulkan* vk_struct);
  ~Interface();

public:
  //Main function
  void fill_profiler_info();
  string get_gpu_name();
  vec4* get_color_background();
  bool is_gpu_discrete();

private:
  vk::structure::Vulkan* vk_struct;
};

}
