#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}
namespace vk::window{class GLFW;}


namespace vk::presentation{

class Surface
{
public:
  //Constructor / Destructor
  Surface(vk::structure::Vulkan* vk_struct);
  ~Surface();

public:
  //Main functions
  void init();
  void clean();

  //Subfunction
  bool check_for_resizing();

private:
  vk::structure::Vulkan* vk_struct;
  vk::window::GLFW* vk_window;
};

}
