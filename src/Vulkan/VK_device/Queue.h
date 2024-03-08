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
  void find_queue_family_composition(vk::structure::Physical_device& physical_device);
  void find_queue_graphics_idx(vk::structure::Physical_device& physical_device);
  void find_queue_transfer_idx(vk::structure::Physical_device& physical_device);
  void find_queue_presentation_idx(vk::structure::Physical_device& physical_device);

  //Subfunction
  bool is_physical_device_queue_suitable(vk::structure::Physical_device& physical_device);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
