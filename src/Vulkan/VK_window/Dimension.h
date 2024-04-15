#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}


namespace vk::window{

class Dimension
{
public:
  //Constructor / Destructor
  Dimension(vk::structure::Vulkan* vk_struct);
  ~Dimension();

public:
  //Main functions
  glm::vec2 get_dimension();
  glm::vec2 get_center();
  void set_center(vec2 value);

private:
  vk::structure::Vulkan* vk_struct;
};

}
