#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}


namespace vk::queue{

class Manager
{
public:
  //Constructor / Destructor
  Manager(vk::structure::Vulkan* vk_struct);
  ~Manager();

public:
  //Main functions
  void init();
  void clean();

private:
  vk::structure::Vulkan* vk_struct;
};

}
