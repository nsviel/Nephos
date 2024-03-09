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
  void assign_queue_family();

  //Subfunction
  bool suitability_for_presentation(vk::structure::Physical_device& physical_device);
  bool suitability_for_graphics(vk::structure::Physical_device& physical_device);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
