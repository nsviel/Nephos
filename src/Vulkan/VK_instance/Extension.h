#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}


namespace vk::instance{

class Extension
{
public:
  //Constructor / Destructor
  Extension(vk::structure::Vulkan* struct_vulkan);
  ~Extension();

public:
  //Main functions
  void init();

  //Subfunction
  void extension_instance();
  void extension_window();
  void extension_device();

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
