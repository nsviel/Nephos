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
  vk::structure::Descriptor_required uniform_point_size();
  vk::structure::Descriptor_required uniform_mvp();
  vk::structure::Descriptor_required uniform_edl();
  vk::structure::Descriptor_required sampler_color();
  vk::structure::Descriptor_required sampler_depth();

private:
  vk::structure::Vulkan* vk_struct;
};

}
