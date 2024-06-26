#pragma once

#include <vector>

namespace vk::structure{class Vulkan;}
namespace prf::hardware{class Structure;}
namespace prf::hardware{class Device;}
namespace utl::hardware{class Nvidia;}


namespace prf::hardware{

class Collector
{
public:
  //Constructor / Destructor
  Collector(prf::hardware::Structure* prf_struct);
  ~Collector();

public:
  //Profiler vulkan info
  void collect_info(vk::structure::Vulkan* vk_struct);
  void collect_gpu_info();

  //Subfunction
  void collect_vulkan_device(vk::structure::Vulkan* vk_struct);

private:
  prf::hardware::Structure* prf_struct;
  utl::hardware::Nvidia* utl_nvidia;
};

}
