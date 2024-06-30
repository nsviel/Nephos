#pragma once

#include <vector>

namespace prf{class Node;}
namespace prf{class Structure;}
namespace prf::hardware{class Device;}
namespace utl::hardware{class Nvidia;}
namespace vk{class Structure;}
namespace vk::queue::structure{class Queue;}


namespace prf::hardware{

class GPU
{
public:
  //Constructor / Destructor
  GPU(prf::Node* node_profiler);
  ~GPU();

public:
  //Profiler vulkan info
  void collect_info();

  //Subfunction
  void collect_gpu_info();
  void collect_vulkan_device();
  void collect_vulkan_queue();
  void add_queue(vk::queue::structure::Queue& queue, int type);

private:
  prf::Structure* prf_struct;
  vk::Structure* vk_struct;
  utl::hardware::Nvidia* utl_nvidia;
};

}
