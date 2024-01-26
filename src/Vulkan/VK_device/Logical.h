#pragma once

#include <Utility/Specific/common.h>

namespace vk::device{class Physical;}
namespace vk::structure{class Vulkan;}


namespace vk::device{

class Logical
{
public:
  //Constructor / Destructor
  Logical(vk::structure::Vulkan* struct_vulkan);
  ~Logical();

public:
  //Main functions
  void init();
  void clean();

  //Subfunction
  void create_logical_device();
  void find_device_queue_handles();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::device::Physical* dev_physical;
};

}
