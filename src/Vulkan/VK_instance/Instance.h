#pragma once

#include <Utility/Specific/common.h>

class VK_validation;
namespace vk::structure{class Vulkan;}


namespace vk::instance{

class Instance
{
public:
  //Constructor / Destructor
  Instance(vk::structure::Vulkan* struct_vulkan);
  ~Instance();

public:
  //Main functions
  void init();
  void clean();

  //Subfunction
  void create_instance();

private:
  VK_validation* vk_validation;
  vk::structure::Vulkan* struct_vulkan;
};

}
