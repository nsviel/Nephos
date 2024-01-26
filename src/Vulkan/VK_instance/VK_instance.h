#pragma once

#include <Utility/Specific/common.h>

class VK_validation;
namespace vk::structure{class Vulkan;}


namespace vk::instance{

class VK_instance
{
public:
  //Constructor / Destructor
  VK_instance(vk::structure::Vulkan* struct_vulkan);
  ~VK_instance();

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
