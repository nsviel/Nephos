#pragma once

namespace vk::structure{class Vulkan;}


namespace vk::instance{

class Extension
{
public:
  //Constructor / Destructor
  Extension(vk::structure::Vulkan* vk_struct);
  ~Extension();

public:
  //Main function
  void init();

  //Subfunction
  void extension_instance();
  void extension_window();
  void extension_device();

private:
  vk::structure::Vulkan* vk_struct;
};

}
