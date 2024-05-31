#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Descriptor;}
namespace vk::structure{class Descriptor_required;}


namespace vk::binding{

class Type
{
public:
  //Constructor / Destructor
  Type(vk::structure::Vulkan* vk_struct);
  ~Type();

public:
  //Main functions
  void uniform_point_size(vk::structure::Descriptor_required& descriptor);
  void uniform_mvp(vk::structure::Descriptor_required& descriptor);
  void sampler_color(vk::structure::Descriptor_required& descriptor);

private:
  vk::structure::Vulkan* vk_struct;
};

}
