#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}


namespace vk::instance{

class Query
{
public:
  //Constructor / Destructor
  Query(vk::structure::Vulkan* struct_vulkan);
  ~Query();

public:
  //Main functions


private:
  vk::structure::Vulkan* struct_vulkan;
};

}
