#pragma once

#include <vector>

namespace vk::structure{class Vulkan;}
namespace prf::hardware{class Structure;}
namespace prf::hardware{class Device;}


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

  //Subfunction
  void collect_vulkan_device(vk::structure::Vulkan* vk_struct);

private:
  prf::hardware::Structure* prf_struct;
  std::vector<prf::hardware::Device> vec_device;
};

}
