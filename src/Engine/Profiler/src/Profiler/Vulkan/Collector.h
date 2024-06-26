#pragma once

#include <vector>

namespace vk::structure{class Vulkan;}
namespace prf::vulkan{class Info;}
namespace prf::vulkan{class Device;}


namespace prf::vulkan{

class Collector
{
public:
  //Constructor / Destructor
  Collector(prf::vulkan::Info* prf_info);
  ~Collector();

public:
  //Profiler vulkan info
  void collect_info(vk::structure::Vulkan* vk_struct);

  //Subfunction
  void collect_vulkan_info(vk::structure::Vulkan* vk_struct);
  void collect_vulkan_device(vk::structure::Vulkan* vk_struct);

private:
  prf::vulkan::Info* prf_info;
  std::vector<prf::vulkan::Device> vec_device;
};

}
