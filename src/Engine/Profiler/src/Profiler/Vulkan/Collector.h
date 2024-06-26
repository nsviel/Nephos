#pragma once

#include <vector>

namespace vk::structure{class Vulkan;}
namespace prf::vulkan{class Structure;}
namespace prf::vulkan{class Device;}


namespace prf::vulkan{

class Collector
{
public:
  //Constructor / Destructor
  Collector(prf::vulkan::Structure* prf_struct);
  ~Collector();

public:
  //Profiler vulkan info
  void collect_info(vk::structure::Vulkan* vk_struct);

  //Subfunction
  void collect_vulkan_device(vk::structure::Vulkan* vk_struct);

private:
  prf::vulkan::Structure* prf_struct;
  std::vector<prf::vulkan::Device> vec_device;
};

}
