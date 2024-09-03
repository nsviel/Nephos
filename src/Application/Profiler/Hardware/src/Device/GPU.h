#pragma once

#include <vector>

namespace prf::hardware{class Node;}
namespace prf::hardware{class Structure;}
namespace prf::hardware{class Device;}
namespace sys::hardware{class Nvidia;}
namespace vk{class Structure;}
namespace vk::queue::structure{class Queue;}


namespace prf::hardware{

class GPU
{
public:
  //Constructor / Destructor
  GPU(prf::hardware::Node* node_hardware);
  ~GPU();

public:
  //Main function
  void collect_gpu_info();
  void collect_gpu_variable();
  void collect_vulkan_info();

  //Subfunction
  void collect_vulkan_device();
  void collect_vulkan_queue();
  void add_queue(vk::queue::structure::Queue& queue, int type);

private:
  prf::hardware::Structure* prf_struct;
  vk::Structure* vk_struct;
  sys::hardware::Nvidia* utl_nvidia;
};

}
