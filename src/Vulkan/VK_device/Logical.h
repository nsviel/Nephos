#pragma once

#include <Utility/Specific/Common.h>

namespace vk::device{class Physical;}
namespace vk::structure{class Vulkan;}
namespace vk::device{class Queue;}


namespace vk::device{

class Logical
{
public:
  //Constructor / Destructor
  Logical(vk::structure::Vulkan* vk_struct);
  ~Logical();

public:
  //Main function
  void init();
  void clean();

  //Subfunction
  void create_logical_device();
  void create_device_queue();

private:
  vk::structure::Vulkan* vk_struct;
  vk::device::Physical* vk_dev_physical;
  vk::device::Queue* vk_dev_queue;
};

}
