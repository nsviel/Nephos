#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk::binding::structure{class Descriptor;}


namespace vk::pipeline::topology{

//Uniform
vk::binding::structure::Descriptor uniform_mvp();
vk::binding::structure::Descriptor uniform_mvp_str();
vk::binding::structure::Descriptor uniform_point_size();

}
