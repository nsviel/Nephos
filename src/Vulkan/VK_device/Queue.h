#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Physical_device;}


namespace vk::device{

class Queue
{
public:
  //Constructor / Destructor
  Queue(vk::structure::Vulkan* struct_vulkan);
  ~Queue();

public:
  //Main functions
  void find_queue_nb_family(vk::structure::Physical_device& dev_physical);
  void find_queue_graphics_idx(vk::structure::Physical_device& dev_physical);
  void find_queue_transfer_idx(vk::structure::Physical_device& dev_physical);
  void find_queue_presentation_idx(vk::structure::Physical_device& dev_physical);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
