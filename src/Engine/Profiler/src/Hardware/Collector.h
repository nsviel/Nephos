#pragma once

#include <vector>

namespace prf{class Node;}
namespace prf{class Structure;}
namespace prf::hardware{class Device;}
namespace utl::hardware{class Nvidia;}
namespace vk{class Structure;}


namespace prf::hardware{

class Collector
{
public:
  //Constructor / Destructor
  Collector(prf::Node* node_profiler);
  ~Collector();

public:
  //Profiler vulkan info
  void collect_info();

  //Subfunction
  void collect_gpu_info();
  void collect_vulkan_device();

private:
  prf::Structure* prf_struct;
  vk::Structure* vk_struct;
  utl::hardware::Nvidia* utl_nvidia;
};

}
